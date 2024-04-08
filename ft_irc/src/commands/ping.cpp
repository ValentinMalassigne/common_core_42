/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlot <acharlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:34:14 by acharlot          #+#    #+#             */
/*   Updated: 2024/02/19 15:34:15 by acharlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/ircserv.hpp"

/**
 * *Prototype for the command 	=> `/ping server`
*/

/**
 * @brief Responds to a PING command from a client with a PONG message.
 * 
 * This function constructs a PONG message with the provided parameters and
 * sends it to the client identified by the file descriptor.
 * 
 * @param server Pointer to the server object.
 * @param client_fd File descriptor of the client.
 * @param cmd Reference to the structure containing command information.
 * @return An integer indicating the success status of the operation.
 */
int	ping(Server *server, int const client_fd, s_cmd &cmd){
	Client		&client		= retrieveClient(server, client_fd);
	std::string	nickname	= client.getNickname();
	std::string	username	= client.getUsername();

	if (cmd.message[0] == ' ')
		cmd.message.erase(0, 1);
	cmd.message.insert(0, ":");
	addToClientBuffer(server, client_fd, RPL_PONG(user_id(nickname, username), cmd.message));

	return (SUCCESS);
}