/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlot <acharlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:37:42 by acharlot          #+#    #+#             */
/*   Updated: 2024/02/23 10:44:15 by acharlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/ircserv.hpp"

/**
 * @brief Limits the number of users in a channel.
 * 
 * This function limits the number of users in a channel by setting a capacity limit.
 * It checks if the channel exists and retrieves its iterator.
 * If the mode starts with '+', it sets the capacity limit to the specified value if it's valid and adds the mode 'l'.
 * If the mode starts with '-', it removes the capacity limit by setting it to -1 and removes the mode 'l'.
 * 
 * @param server Pointer to the server object.
 * @param datas Array containing channel name, mode, and limit information.
 * @param client_fd File descriptor of the client.
 */
void	limitChannelMode(Server *server, std::string datas[4], int const client_fd){
	if (server->isChannel(datas[1]) == false){
		addToClientBuffer(server, client_fd, ERR_NOSUCHCHANNEL(datas[0], datas[1]));
		return ;
	}
	std::map<std::string, Channel>::iterator	it;
	it = server->getChannels().find(datas[1]);
	int limit = atoi(datas[3].c_str());
	if (datas[2][0] == '+'){
		if (limit < 0 || (int)it->second.getClientList().size() > limit)
			return ;
		
		it->second.setCapacityLimit(limit);
		size_t	pos = it->second.getMode().find("l");
		if (pos != std::string::npos)
			return ;
		it->second.addMode("l");
		std::ostringstream ss;
		ss << limit;
		broadcastToAllChannelMembers(server, it->second, MODE_CHANNELMSGWITHPARAM(datas[1], "+l", ss.str()));
	}
	else if (datas[2][0] == '-'){
		limit = -1;
		it->second.setCapacityLimit(limit);
		size_t pos = it->second.getMode().find("l");
		if (pos == std::string::npos)
			return ;
		it->second.removeMode("l");
		broadcastToAllChannelMembers(server, it->second, MODE_CHANNELMSG(datas[1], "-l"));
	}
}