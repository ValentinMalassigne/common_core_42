/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlot <acharlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:38:03 by acharlot          #+#    #+#             */
/*   Updated: 2024/02/27 14:16:50 by acharlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/ircserv.hpp"


/**
 * @brief Modify the mode of a channel to grant or revoke operator status to a user.
 * 
 * This function modifies the mode of a channel to grant or revoke operator status to a user.
 * 
 * @param server Pointer to the Server instance.
 * @param mode_infos Structure containing mode information.
 * @param client_fd File descriptor of the client making the request.
 * @param str The mode string.
 */
void	operatorChannelMode(Server *server, s_mode mode_infos, int const client_fd, std::string str){
	std::map<const int, Client>::iterator it_client = server->getClients().find(client_fd);
	std::map<std::string, Channel>::iterator it_channel_target = server->getChannels().find(mode_infos.target);
	
	if (mode_infos.params.empty() == true){
		return ;
	}

	std::map<const int, Client>::iterator it_user_target = server->getClients().begin();
	while (it_user_target != server->getClients().end()){
		if (it_user_target->second.getNickname() == mode_infos.params)
			break;
		it_user_target++;
	}
	if (it_user_target == server->getClients().end()){
		addToClientBuffer(server, client_fd, ERR_NOSUCHNICK(it_client->second.getNickname(), mode_infos.params));
		addToClientBuffer(server, client_fd, ERR_USERNOTINCHANNEL(it_client->second.getNickname(), mode_infos.params, mode_infos.target));
		return ;
	}
	if (it_channel_target->second.getClientList().find(mode_infos.params) == it_channel_target->second.getClientList().end()){
		addToClientBuffer(server, client_fd, ERR_USERNOTINCHANNEL(it_client->second.getNickname(), mode_infos.params, mode_infos.target));
		return ;
	}
	std::vector<std::string>::iterator it;
	for (it = it_channel_target->second.getOperators().begin(); it != it_channel_target->second.getOperators().end(); it++){
		if (*it == mode_infos.params)
			break;
	}
	
	if (str[0] == '+'){
		if (it != it_channel_target->second.getOperators().end())
			return ;
		
		it_channel_target->second.getOperators().push_back(mode_infos.params);
		broadcastToAllChannelMembers(server, it_channel_target->second, MODE_CHANNELMSGWITHPARAM(mode_infos.target, "+o", mode_infos.params));
	}
	else{
		if (it == it_channel_target->second.getOperators().end())
			return ;
		it_channel_target->second.getOperators().erase(it);
		broadcastToAllChannelMembers(server, it_channel_target->second, MODE_CHANNELMSGWITHPARAM(mode_infos.target, "-o", mode_infos.params));
	}
	std::cout << "check operators: " << std::endl;
	for (std::vector<std::string>::iterator it = it_channel_target->second.getOperators().begin(); it != it_channel_target->second.getOperators().end(); it++)
		std::cout << *it << std::endl;
}