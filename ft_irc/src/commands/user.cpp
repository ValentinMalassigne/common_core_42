/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlot <acharlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:33:50 by acharlot          #+#    #+#             */
/*   Updated: 2024/02/19 15:33:50 by acharlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/ircserv.hpp"

/**
 * @brief Finds the username from the given message.
 * 
 * This function extracts the username from the provided message.
 * If the message is not empty and starts with a space, the leading space is removed.
 * The username is then extracted from the message until the first space is encountered.
 * 
 * @param msg The message to parse.
 * @return The extracted username.
 */
std::string	findUsername(std::string msg){
	std::string user;
	user.clear();

	if (msg.empty() == false && msg[0] == ' ')
		msg.erase(0, 1);
	if (msg.empty() == false){
		if (msg.find_first_of(' ') != std::string::npos)
			user.insert(0, msg, 0, msg.find(' '));
		else
			user.insert(0, msg, 0, std::string::npos);
	}
	return (user);
}

/**
 * @brief Finds the real name from the given message.
 * 
 * This function extracts the real name from the provided message.
 * If the message is not empty and starts with a space, the leading space is removed.
 * The real name is then extracted from the message after the third space.
 * 
 * @param msg The message to parse.
 * @return The extracted real name.
 */
std::string	findRealname(std::string msg){
	std::string real;
	real.clear();

	if (msg.empty() == false && msg[0] == ' ')
		msg.erase(0, 1);
	if (msg.empty())
		return (real);
	
	int space_count = 0;
	int	begin_pos = 0;
	for (size_t i = 0; i < msg.size(); i++){
		if (msg[i] == ' ')
			space_count++;
		if (space_count == 3){
			begin_pos = i;
			break;
		}
	}
	if (space_count >= 3)
		real.insert(0, msg, begin_pos + 1, std::string::npos); 
	if (real[0] == ':')
		real.erase(0, 1);
	return (real);
}

/**
 * @brief Handles the USER command for setting the username and real name of a client.
 * 
 * This function parses the message to extract the username and real name.
 * If either username or real name is empty, an error message is sent to the client.
 * If the client is already registered, an error message is sent to the client.
 * Otherwise, the username and real name are set for the client.
 * 
 * @param server Pointer to the server object.
 * @param client_fd File descriptor of the client.
 * @param cmd_infos Structure containing command information.
 */
void	user(Server *server, int const client_fd, s_cmd cmd_infos){
	Client&		client		= retrieveClient(server, client_fd);
	std::string	username	= findUsername(cmd_infos.message);
	std::string realname	= findRealname(cmd_infos.message);

	if (username.empty() || realname.empty())
		addToClientBuffer(server, client_fd, ERR_NEEDMOREPARAMS(client.getNickname(), cmd_infos.name));
	else if (client.isRegistrationDone() == true)
		addToClientBuffer(server, client_fd, ERR_ALREADYREGISTERED(client.getNickname()));
	else{
		client.setUsername(username);
		client.setRealname(realname);
		client.setNbInfo(+1);
	}
}
