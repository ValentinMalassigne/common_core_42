/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlot <acharlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:34:45 by acharlot          #+#    #+#             */
/*   Updated: 2024/02/20 13:37:51 by acharlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/ircserv.hpp"

/**
 * *Prototype for the command => `/motd +target`
*/

/**
 * @brief Extract the server name from a message.
 * 
 * This function extracts the server name from a message.
 * 
 * @param msg The message from which to extract the server name.
 * @return The extracted server name.
 */
static std::string	getServer(std::string msg)
{
	std::string servername;
	servername.clear();

	if (msg.empty() == true)
		return (servername);
	
	if (msg.find(' ') == std::string::npos)
		servername.insert(0, msg, 0, std::string::npos);
	else
			servername.insert(0, msg, 1, std::string::npos);
	return (servername);
}

/**
 * @brief Sends the Message of the Day (MOTD) to a client.
 * 
 * This function retrieves the client's nickname and the server name, then attempts to open the MOTD file.
 * If the server name is empty, it sets it to "localhost". If the server name is not "localhost", it sends an error message
 * to the client indicating that the server does not exist. If the MOTD file cannot be opened, it sends an error message
 * to the client indicating that the MOTD file is not available. Otherwise, it reads the MOTD file line by line and sends
 * each line as a separate message to the client, starting with a message indicating the beginning of the MOTD and ending
 * with a message indicating the end of the MOTD.
 * 
 * @param server Pointer to the server object.
 * @param client_fd File descriptor of the client.
 * @param cmd_infos Structure containing command information.
 */
void	motd(Server *server, int const client_fd, s_cmd cmd_infos){
	std::string client = retrieveClient(server, client_fd).getNickname();
	std::string servername = getServer(cmd_infos.message);

	if (servername.empty() == true)
		servername = "localhost";
	if (servername != "localhost"){
		addToClientBuffer(server, client_fd, ERR_NOSUCHSERVER(client, servername));
		return ;
	}

	std::ifstream		data;
	char				filepath[24] = "config/motd.config";

	data.open(filepath);
	if (!data){
		addToClientBuffer(server, client_fd, ERR_NOMOTD(client));
		return ;
	}
	else{
		std::string		motd_lines;
		std::string		buf;
		
		buf = RPL_MOTDSTART(client, servername);
		while (getline(data, motd_lines))
			buf += RPL_MOTD(client, motd_lines);
		buf += RPL_ENDOFMOTD(client);
		addToClientBuffer(server, client_fd, buf);
	}
	data.close();
}
