/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlot <acharlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:34:27 by acharlot          #+#    #+#             */
/*   Updated: 2024/02/19 15:34:27 by acharlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/ircserv.hpp"

/**
 * *Prototype for the command 	=> `/pass password`
*/

/**
 * @brief Retrieves the password from a message.
 * 
 * This function retrieves the password from a message by skipping leading spaces and
 * then appending characters
 * until a space or the end of the message is encountered.
 * 
 * @param msg_to_parse The message containing the password.
 * @return A string containing the retrieved password.
 */
std::string	retrievePassword(std::string msg_to_parse)
{
	std::string	password;
	size_t i = 0;
	
	password.clear();
	
	while (msg_to_parse[i] && msg_to_parse[i] == ' ')
		i++;
	while (msg_to_parse[i] && msg_to_parse[i] != ' ')
		password += msg_to_parse[i++];
	return (password);
}


/**
 * @brief Processes the PASS command received from a client.
 * 
 * This function extracts the password from the PASS command message and compares it with the 
 * server's password. If the password matches, it increments the client's number of 
 * received information.
 * 
 * @param server A pointer to the server instance.
 * @param client_fd The file descriptor of the client.
 * @param cmd_infos The command information structure containing details of the received command.
 * @return SUCCESS if the password is correct and the client's number of received information is 
 * incremented, FAILURE otherwise.
 */
int		pass(Server *server, int const client_fd, s_cmd cmd_infos)
{
	Client&		client		= retrieveClient(server, client_fd);
	std::string	password	= retrievePassword(cmd_infos.message);


	if (cmd_infos.message.empty() == true || password.empty() == true)
	{
		addToClientBuffer(server, client_fd, ERR_NEEDMOREPARAMS(client.getNickname(), cmd_infos.name));
		return (FAILURE);
	}
	else if (server->getPassword() != password)
	{
		addToClientBuffer(server, client_fd, ERR_PASSWDMISMATCH(client.getNickname()));
		if (client.isRegistrationDone() == false)
			client.setNbInfo(-1);
		return (FAILURE);
	}
	else
	{
		client.setNbInfo(+1);
		return (SUCCESS);
	}
}