/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:34:30 by acharlot          #+#    #+#             */
/*   Updated: 2024/03/22 08:45:59 by cpothin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/ircserv.hpp"

/**
 * *Prototype for the command 	=> `/part #channel :Reason`
*/

/**
 * @brief Checks if a string contains at least one alphabetic character.
 * 
 * This function iterates through the characters of the string and checks if
 * any of them is alphabetic using the isalpha function from the C standard library.
 * If at least one alphabetic character is found, it returns true, otherwise it returns false.
 * 
 * @param str The string to check.
 * @return true if the string contains at least one alphabetic character, false otherwise.
 */
static bool			containsAtLeastOneAlphaChar(std::string str)
{
	for (size_t i = 0; i < str.size(); i++){
		if (isalpha(str[i]))
			return (true);
	}
	return (false);
}

/**
 * @brief Handles the PART command for leaving one or more channels.
 * 
 * This function parses the message to extract the channel name(s) and reason.
 * If no channel name is provided, an error message is sent to the client.
 * For each channel name provided, it checks if the client is in the channel.
 * If the channel does not exist, an error message is sent. If the client is not
 * in the channel, another error message is sent. Otherwise, the client is removed
 * from the channel, a part message is sent to the client, and the part message
 * is broadcasted to all members of the channel.
 * 
 * @param server Pointer to the server object.
 * @param client_fd File descriptor of the client.
 * @param cmd_infos Structure containing command information.
 */
void				part(Server *server, int const client_fd, s_cmd cmd_infos){
	Client		client		= retrieveClient(server, client_fd);
	std::string nick		= client.getNickname();
	std::string	channel;

	std::string reason = getReason(cmd_infos.message);
	if (cmd_infos.message.empty() == true){
		addToClientBuffer(server, client_fd, ERR_NEEDMOREPARAMS(nick, cmd_infos.name));
		return ;
	}
	cmd_infos.message.erase(cmd_infos.message.find(reason), reason.length());

	while (containsAtLeastOneAlphaChar(cmd_infos.message) == true){
		channel.clear();
		channel = getChannelName(cmd_infos.message);
		cmd_infos.message.erase(cmd_infos.message.find(channel), channel.length()); 

		std::map<std::string, Channel>&			 channels 	= server->getChannels();
		std::map<std::string, Channel>::iterator it			= channels.find(channel);
		if (it == channels.end())
		{
			addToClientBuffer(server, client_fd, ERR_NOSUCHCHANNEL(nick, channel));
			continue ;
		}
		else if (it != channels.end() \
				&& it->second.doesClientExist(nick) == false){
			addToClientBuffer(server, client_fd, ERR_NOTONCHANNEL(nick, channel));
			continue ;
		}
		else{
			it->second.getClientList().erase(nick);
			addToClientBuffer(server, client_fd, RPL_PART(user_id(nick, client.getUsername()), channel, reason));
			broadcastToAllChannelMembers(server, it->second, client.getUsername());
		}
	}
}