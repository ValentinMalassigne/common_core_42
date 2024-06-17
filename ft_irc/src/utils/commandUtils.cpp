/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandUtils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:33:06 by acharlot          #+#    #+#             */
/*   Updated: 2024/02/24 10:27:54 by axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/ircserv.hpp"

/**
 * @brief Extracts the reason from a message.
 * 
 * This function takes a message as input and extracts the reason part after the ':' character.
 * 
 * @param msg_to_parse The message from which to extract the reason.
 * @return The reason extracted from the message.
 */
std::string	getReason(std::string msg_to_parse){
	std::string reason;
	
	reason.clear();
	
	if (msg_to_parse.find(":") != msg_to_parse.npos) 
		reason.append(msg_to_parse, msg_to_parse.find(":") + 1, std::string::npos);
	return (reason);
}

/**
 * @brief Broadcasts a message to all members of a channel.
 * 
 * This function broadcasts a message to all members of a channel.
 * 
 * @param server A pointer to the Server object.
 * @param channel The Channel object representing the channel.
 * @param reply The message to broadcast.
 */
void	broadcastToAllChannelMembers(Server *server, Channel &channel, std::string reply){
	std::map<std::string, Client>::iterator member = channel.getClientList().begin();

	while(member != channel.getClientList().end()){
		addToClientBuffer(server, member->second.getClientFd(), reply);
		member++;
	}
}