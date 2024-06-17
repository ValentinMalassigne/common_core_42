/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:36:47 by acharlot          #+#    #+#             */
/*   Updated: 2024/02/24 10:57:21 by axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/ircserv.hpp"

/**
 * *Prototype for the command => `/invite nickname #channel`
*/

/**
 * @brief Finds and extracts the channel name from a message string.
 * 
 * This function extracts the channel name from a message string if it contains
 * a '#' character. It returns an empty string if the input message is empty
 * or does not contain a '#' character.
 * 
 * @param msg_to_parse The message string to parse.
 * @return std::string The extracted channel name.
 */
std::string	findChannel(std::string msg_to_parse){
	std::string	channel;

	if (msg_to_parse.empty() || msg_to_parse.find("#") == msg_to_parse.npos)
		channel.clear();
	else
		channel.append(msg_to_parse, msg_to_parse.find("#") + 1, std::string::npos);
	return (channel);
}

/**
 * @brief Finds and extracts the nickname from a message string.
 * 
 * This function extracts the nickname from the first word of a message string
 * delimited by spaces. If the message is empty or the first word contains a '#'
 * character, an empty string is returned.
 * 
 * @param msg_to_parse The message string to parse.
 * @return std::string The extracted nickname.
 */
std::string	findNickname(std::string msg_to_parse){
	std::string	nickname;
	nickname.clear();

	if (msg_to_parse.empty() == true)
		return (nickname);
	char *str = const_cast<char *>(msg_to_parse.data());
	nickname = strtok(str, " ");

	if (nickname.empty() || nickname.find("#") != nickname.npos)
		nickname.clear();
	return (nickname);
}

/**
 * @brief Handles the INVITE command.
 * 
 * This function processes the INVITE command, inviting a client to join a specified channel.
 * It checks for various error conditions and sends appropriate responses to the client.
 * 
 * @param server A pointer to the Server object.
 * @param client_fd The file descriptor of the client.
 * @param cmd_infos The parsed command information.
 */
void	invite(Server *server, int const client_fd, s_cmd cmd_infos){
	Client&	client				= retrieveClient(server, client_fd);
	std::string	client_nickname	= client.getNickname();
	std::string channel_name 	= findChannel(cmd_infos.message);
	std::string invited_client	= findNickname(cmd_infos.message);
	
	if (client_nickname.empty() || channel_name.empty()){
		addToClientBuffer(server, client_fd, ERR_NEEDMOREPARAMS(client_nickname, cmd_infos.name));
		return ;
	}

	std::map<std::string, Channel>&				channels = server->getChannels();
	std::map<std::string, Channel>::iterator 	channel = channels.find(channel_name);
	if (channel == channels.end()){
		addToClientBuffer(server, client_fd, ERR_NOSUCHCHANNEL(client_nickname, channel_name));
		return ;
	}

	if (channel->second.doesClientExist(client_nickname) == false){
		addToClientBuffer(server, client_fd, ERR_NOTONCHANNEL(client_nickname, channel_name));
		return ;
	}

	if (channel->second.doesClientExist(invited_client) == true){
		addToClientBuffer(server, client_fd, ERR_USERONCHANNEL(client_nickname, invited_client, channel_name));
		return ;
	}
	
	channel->second.addInvitedUser(invited_client);

	addToClientBuffer(server, client_fd,
		RPL_INVITING(user_id(client_nickname, client.getUsername()), client_nickname, invited_client, channel_name));

	std::map<const int, Client>&			clients = server->getClients();
	std::map<const int, Client>::iterator	it;
	for (it = clients.begin(); it != clients.end(); it++){
		if (it->second.getNickname() == invited_client){
			addToClientBuffer(server, it->second.getClientFd(),
				RPL_INVITE(user_id(client_nickname, client.getUsername()), it->second.getNickname(), channel_name));
			break ;
		}
	}
}