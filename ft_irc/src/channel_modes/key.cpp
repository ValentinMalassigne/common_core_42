/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlot <acharlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:37:23 by acharlot          #+#    #+#             */
/*   Updated: 2024/02/20 14:17:58 by acharlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/ircserv.hpp"

/**
 * @brief Checks if a string contains only alphabetic characters.
 * 
 * This function checks if the given string contains only alphabetic characters.
 * 
 * @param str The string to check.
 * @return True if the string contains only alphabetic characters, false otherwise.
 */
static bool	isAlpha(std::string str){
	for (size_t i = 0; i < str.length(); i++){
		if (!isalpha(str[i]))
			return (false);
	}
	return (true);
}

/**
 * @brief Sets or removes the channel key mode.
 * 
 * This function sets or removes the channel key mode for a specified channel.
 * 
 * @param server Pointer to the Server object.
 * @param mode_infos Mode information struct containing target channel and mode parameters.
 * @param client_fd File descriptor of the client requesting the mode change.
 * @param mode_str Mode string indicating whether to set or remove the mode.
 */
void	keyChannelMode(Server *server, s_mode mode_infos, int const client_fd, std::string mode_str){
	std::map<const int, Client>::iterator it_client = server->getClients().find(client_fd);
	std::map<std::string, Channel>::iterator it_channel_target = server->getChannels().find(mode_infos.target);

	size_t	pos = it_channel_target->second.getMode().find("k");
	if (mode_infos.params.empty() == true)
		return ;
	
	if (mode_str[0] == '+'){
		if (pos != std::string::npos)
			return;
		if (isAlpha(mode_infos.params) == false){
			addToClientBuffer(server, client_fd, ERR_INVALIDMODEPARAM(it_client->second.getNickname(), mode_infos.target, "+k", mode_infos.params));
			return ;
		}
		it_channel_target->second.addMode("k");
		it_channel_target->second.setChannelPassword(mode_infos.params);
		broadcastToAllChannelMembers(server, it_channel_target->second, MODE_CHANNELMSGWITHPARAM(mode_infos.target, "+k", mode_infos.params));
	}
	else {
		if (pos == std::string::npos)
			return ;
		it_channel_target->second.removeMode("k");
		it_channel_target->second.removeChannelPassword();
		broadcastToAllChannelMembers(server, it_channel_target->second, MODE_CHANNELMSGWITHPARAM(mode_infos.target, "-k", mode_infos.params));
	}
}