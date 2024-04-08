/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:34:42 by acharlot          #+#    #+#             */
/*   Updated: 2024/02/24 10:34:36 by axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/ircserv.hpp"

/**
 * *Prototype for the command => `/names #optionnal_channel`
*/

/**
*    @brief Checks if a string contains at least one alphanumeric character, hyphen, or underscore.
*  
*	 This function iterates through the characters of the given string and checks if it contains at least
*    one alphanumeric character (a-z, A-Z, 0-9), hyphen (-), or underscore (_).
*
*    @param str The string to check for alphanumeric characters, hyphens, or underscores.
*
*    @return True if the string contains at least one alphanumeric character, hyphen, or underscore; otherwise, false.
*/
static bool		containsAtLeastOneAlphaChar(std::string str){
	for (size_t i = 0; i < str.size(); i++){
		if (isalpha(str[i]) || str[i] == '_' || str[i] == '-' || isdigit(str[i]))
			return (true);
	}
	return (false);
}

/**
*    @brief Extracts a channel name from a given message.
*
*    This function parses the given message to extract a channel name.
*    The channel name is extracted based on the characters that are considered valid
*    in a channel name, which include letters (a-z, A-Z), digits (0-9), hyphens (-), and underscores (_).
*    @param msg_to_parse The message from which to extract the channel name.
*    
*	 @return The extracted channel name.
*/
static std::string getaChannelName(std::string msg_to_parse){
	std::string	channel_name;
	size_t		i = 0;

	while (msg_to_parse[i] && (!isalpha(msg_to_parse[i]) && !isdigit(msg_to_parse[i]) && msg_to_parse[i] != '-' && msg_to_parse[i] != '_'))
		i++;
	while (msg_to_parse[i] && (isalpha(msg_to_parse[i]) || msg_to_parse[i] == '-' 
		|| msg_to_parse[i] == '_' || isdigit(msg_to_parse[i]))){
		channel_name += msg_to_parse[i];
		i++;
	}
	return (channel_name);
}


/**
 * @brief Retrieves the list of users in a channel and sends it to the client.
 * 
 * This function retrieves the list of users in the specified channel and sends
 * it to the client who requested it. It iterates through the message to find the
 * channel name(s) and fetches the list of members accordingly. It then constructs
 * the appropriate reply messages and sends them to the client.
 * 
 * @param server A pointer to the Server object.
 * @param client_fd The file descriptor of the client.
 * @param cmd_infos The structure containing information about the command.
 */
void	names(Server *server, int const client_fd, s_cmd cmd_infos){
	Client			client				= retrieveClient(server, client_fd);
	std::string		symbol				= "=";
	std::string		channel_to_name;
	std::string		list_of_members;

	if (cmd_infos.message.empty() == true){
		addToClientBuffer(server, client_fd, ERR_NEEDMOREPARAMS(client.getNickname(), cmd_infos.name));
		return ;
	}
	while (containsAtLeastOneAlphaChar(cmd_infos.message) == true){
		channel_to_name.clear();
		channel_to_name = getaChannelName(cmd_infos.message);
		cmd_infos.message.erase(cmd_infos.message.find(channel_to_name), channel_to_name.length()); 

		std::map<std::string, Channel>				channels = server->getChannels();
		std::map<std::string, Channel>::iterator	channel = channels.find(channel_to_name);
		if (channel == channels.end()
			|| (channel->second.doesClientExist(client.getNickname()) == false
			&& channel->second.getMode().find('s') != std::string::npos)){
			addToClientBuffer(server, client_fd, RPL_ENDOFNAMES(client.getNickname(), channel_to_name));
			continue ;
		}
			
		symbol.clear();
		symbol = getSymbol(channel->second);

		list_of_members.clear();
		list_of_members = getListOfMembers(client.getNickname(), channel->second);

		if (list_of_members.empty() == false)
			addToClientBuffer(server, client_fd, RPL_NAMREPLY(client.getNickname(), symbol, channel_to_name, list_of_members));
		addToClientBuffer(server, client_fd, RPL_ENDOFNAMES(client.getNickname(), channel_to_name));
	}
}