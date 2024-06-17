/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:36:32 by acharlot          #+#    #+#             */
/*   Updated: 2024/03/22 17:30:04 by cpothin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/ircserv.hpp"

/**
 * *Need to be an operators.
 * *Prototype for the command => `/kick #channel nickname :Reason`
*/

/**
 * @brief Extracts the kicked client's name from a kick message.
 * 
 * This function takes a message as input and extracts the name of the client who was 
 * kicked from the message.
 * 
 * @param msg_to_parse The message from which to extract the kicked client's name.
 * @return The name of the kicked client.
 */
static std::string	getKickedName(std::string msg_to_parse){
	std::string	kicked;

	if (msg_to_parse[0] == ' ')
		msg_to_parse.erase(0, 1);
	kicked = msg_to_parse.substr(msg_to_parse.find(' ') + 1, (msg_to_parse.find(':') - 1 - (msg_to_parse.find(' ') + 1)));
	return (kicked);
}

/**
 * @brief Broadcasts a kick message to all clients in a channel.
 * 
 * This function sends a kick message to all clients in the specified channel, indicating
 * that a particular client has been kicked from the channel with a given reason.
 * 
 * @param server The server instance.
 * @param channel The channel from which the client is being kicked.
 * @param client The client who initiated the kick.
 * @param kicked The nickname of the client being kicked.
 * @param reason The reason for the kick.
 */
static void	broadcastToChannel(Server *server, Channel &channel, Client &client, 
	std::string kicked, std::string reason){
	std::map<std::string, Client>::iterator	member = channel.getClientList().begin();

	while (member != channel.getClientList().end()){
		addToClientBuffer(server, member->second.getClientFd(), \
			RPL_KICK(user_id(client.getNickname(), client.getUsername()), channel.getName(), kicked, reason));
		member++;
	}
}


/**
 * @brief Kicks a client from a channel.
 * 
 * This function kicks a specified client from a channel. The client must be a member of the channel
 * and the requester must have operator privileges in the channel to perform this action.
 * 
 * @param server The server instance.
 * @param client_fd The file descriptor of the client initiating the kick.
 * @param cmd_infos The parsed command information.
 */
void				kick(Server *server, int const client_fd, s_cmd cmd_infos){
	Client& 									requester		= retrieveClient(server, client_fd);
	std::string									requester_name	= requester.getNickname();
	std::string									channel_name	= getChannelName(cmd_infos.message);
	std::string									kicked_name		= getKickedName(cmd_infos.message);
	std::string									reason			= getReason(cmd_infos.message);
	std::map<std::string, Channel>&				channels		= server->getChannels();
	std::map<std::string, Channel>::iterator 	it_chan			= channels.find(channel_name);
	
	reason = (reason.empty()) ? ":Kicked by the channel's operator" : reason;

	if (channel_name.empty() || kicked_name.empty()){
		addToClientBuffer(server, client_fd, ERR_NEEDMOREPARAMS(requester_name, cmd_infos.name));
		return ;
	}
	else if (requester_name == kicked_name){
		addToClientBuffer(server, client_fd, ERR_CANTKICKYOURSELF(requester_name, channel_name));
		return ;
	}
	else if (it_chan == channels.end()){
		addToClientBuffer(server, client_fd, ERR_NOSUCHCHANNEL(requester_name, channel_name));
		return ;
	}
	else if (it_chan->second.doesClientExist(requester_name) == false){
		addToClientBuffer(server, client_fd, ERR_NOTONCHANNEL(requester_name, channel_name));
		return ;
	}
	else if (it_chan->second.doesClientExist(kicked_name) == false){
		addToClientBuffer(server, client_fd, ERR_USERNOTINCHANNEL(requester_name, kicked_name, channel_name));
		return ;
	}
	else if (it_chan->second.isOperator(requester_name) == false){
		addToClientBuffer(server, client_fd, ERR_CHANOPRIVSNEEDED(requester_name, channel_name));
		return ;
	}
	else{
		broadcastToChannel(server, it_chan->second, requester, kicked_name, reason);
		// it_chan->second.getClientList().erase(kicked_name);
		it_chan->second.removeClientFromChannel(kicked_name);
	}
}