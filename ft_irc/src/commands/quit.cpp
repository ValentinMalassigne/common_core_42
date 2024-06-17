/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlot <acharlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:34:04 by acharlot          #+#    #+#             */
/*   Updated: 2024/02/19 15:34:05 by acharlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/ircserv.hpp"

/**
 * *Prototype for the command 	=> `/quit :Reason`
*/

/**
 * @brief Broadcasts a quit message to all members of a channel.
 * 
 * This function sends a quit message to all members of the specified channel
 * except the client who is quitting. It iterates through the client list
 * of the channel and sends the quit message to each member.
 * 
 * @param server Pointer to the server object.
 * @param channel Reference to the channel object.
 * @param client_fd File descriptor of the client who is quitting.
 * @param nick Nickname of the client who is quitting.
 * @param user Username of the client who is quitting.
 * @param reason Reason for quitting.
 */
static void	broadcastToChan(Server *server, Channel &channel, int const client_fd, 
std::string nick, std::string user, std::string reason){
	std::map<std::string, Client>::iterator member = channel.getClientList().begin();
	
	(void) client_fd;
	while (member != channel.getClientList().end()){
		if (member->second.getClientFd() != client_fd){
			addToClientBuffer(server, member->second.getClientFd(), \
				RPL_QUIT(user_id(nick, user), reason));
		}	
		member++;
	}
}

/**
 * @brief Removes a client from all channels on the server.
 * 
 * This function removes the specified client from all channels on the server.
 * It iterates through the channels and removes the client from the client list
 * of each channel if the client exists in the channel.
 * 
 * @param server Pointer to the server object.
 * @param killed_user Nickname of the client to be removed.
 */
static void	removeFromServer(Server *server, std::string killed_user){
	std::map<std::string, Channel>&				channels = server->getChannels();
	std::map<std::string, Channel>::iterator	chan;
	for (chan = channels.begin(); chan != channels.end(); chan++){
		if (chan->second.doesClientExist(killed_user))
			chan->second.getClientList().erase(killed_user);
	}
}

/**
 * @brief Handles the QUIT command for disconnecting a client from the server.
 * 
 * This function sends a quit message to all channels the client is a member of,
 * removes the client from all channels, sets the client's disconnection status,
 * and removes the client from the server.
 * 
 * @param server Pointer to the server object.
 * @param client_fd File descriptor of the client.
 * @param cmd_infos Structure containing command information.
 */
void		quit(Server *server, int const client_fd, s_cmd cmd_infos){
	Client& 								  client   = retrieveClient(server, client_fd);
	std::string								  reason   = getReason(cmd_infos.message);
	std::map<std::string, Channel>&			  channels = server->getChannels();
	std::map<std::string, Channel>::iterator  chan	   = channels.begin();

	addToClientBuffer(server, client_fd, RPL_QUIT(user_id(client.getNickname(), client.getUsername()), reason));

	for (; chan != channels.end(); chan++){
		std::map<std::string, Client>& 			chan_members = chan->second.getClientList();
		std::map<std::string, Client>::iterator	member		 = chan_members.begin();
		for (; member != chan_members.end(); member++){
			if (member->second.getClientFd() == client_fd){
				chan_members.erase(client.getNickname());
				broadcastToChan(server, chan->second, client_fd, client.getNickname(), client.getUsername(), reason);
				break ;
			}
		}
	}
	client.setDeconnexionStatus(true);
	removeFromServer(server, client.getNickname());
}