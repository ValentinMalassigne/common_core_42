/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:34:07 by acharlot          #+#    #+#             */
/*   Updated: 2024/03/25 18:35:28 by cpothin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/ircserv.hpp"

/**
 * *Prototype for the command 		=> `/msg nickname : 'msg' for an user.'
 * *								=> `/msg #channel : 'msg' for a channel.'
 * To switch channels and privates messages, you can use CTRL+P and CTRL+N.
*/

/**
 * @brief Broadcasts a message to all members of a channel except the sender.
 * 
 * This function checks if the sender is banned or kicked from the channel.
 * If banned or kicked, appropriate error messages are sent to the client.
 * If the channel is moderated and the sender is not operator or voiced, an error message is sent.
 * Otherwise, the message is sent to all members of the channel.
 * 
 * @param server Pointer to the server object.
 * @param client_fd File descriptor of the client sending the message.
 * @param it_client Iterator pointing to the client in the client list.
 * @param it_channel Iterator pointing to the channel in the channel list.
 * @param target The target channel name.
 * @param msg_to_send The message to send.
 */
static void  broadcastToChannel(Server *server, int const client_fd, std::map<const int, Client>::iterator it_client,
std::map<std::string, Channel>::iterator it_channel, std::string target, std::string msg_to_send){
	std::map<std::string, Client>::iterator member = it_channel->second.getClientList().begin();
	while (member != it_channel->second.getClientList().end())
	{
		if (member->second.getClientFd() != client_fd)
			addToClientBuffer(server, member->second.getClientFd(), RPL_PRIVMSG(it_client->second.getNickname(), it_client->second.getUsername(), target, msg_to_send));
		member++;
	}
	}

/**
 * @brief Broadcasts a message to all members of a channel except the sender.
 * 
 * This function checks if the sender is banned or kicked from the channel.
 * If banned or kicked, appropriate error messages are sent to the client.
 * If the channel is moderated and the sender is not operator or voiced, an error message is sent.
 * Otherwise, the message is sent to all members of the channel.
 * 
 * @param server Pointer to the server object.
 * @param client_fd File descriptor of the client sending the message.
 * @param it_client Iterator pointing to the client in the client list.
 * @param it_channel Iterator pointing to the channel in the channel list.
 * @param target The target channel name.
 * @param msg_to_send The message to send.
 */
static bool isUserinChannel(std::map<const int, Client>::iterator it_client, std::map<std::string, Channel>::iterator it_channel){
	if (it_channel->second.getClientList().find(it_client->second.getNickname()) != it_channel->second.getClientList().end())
		return (true);
	return (false);
}

/**
 * @brief Handles the PRIVMSG command for sending private or channel messages.
 * 
 * This function parses the message to extract the target and message to send.
 * If the target is a channel, the message is broadcasted to all members of the channel.
 * If the target is a user, the message is sent directly to the user.
 * 
 * @param server Pointer to the server object.
 * @param client_fd File descriptor of the client sending the message.
 * @param cmd_infos Structure containing command information.
 */
void	privmsg(Server *server, int const client_fd, s_cmd cmd_infos){ 
	std::map<const int, Client>				&client_list = server->getClients();
	std::map<std::string, Channel> 			channel_list = server->getChannels(); 
	std::map<const int, Client>::iterator 	it_client = client_list.find(client_fd);
	std::string 							target;
	std::string 							msg_to_send;

	size_t      delimiter = cmd_infos.message.rfind(":");
	if (delimiter == std::string::npos){
		addToClientBuffer(server, client_fd, ERR_NOTEXTTOSEND(it_client->second.getNickname()));
		return ;
	}
	target = cmd_infos.message.substr(1, delimiter - 1);
	if (target.empty()){
		addToClientBuffer(server, client_fd, ERR_NORECIPIENT(it_client->second.getNickname()));
		return ;
	}
		
	msg_to_send = cmd_infos.message.substr(delimiter);

	delimiter = target.find(" ");
	if (delimiter != std::string::npos)
		target.erase(delimiter);  

	if (target[0] == '#'){
		std::map<std::string, Channel>::iterator it_channel = channel_list.find(target.substr(1));

		if (it_channel == channel_list.end())
			addToClientBuffer(server, client_fd, ERR_NOSUCHNICK(it_client->second.getNickname(), target));
		else
			broadcastToChannel(server, client_fd, it_client, it_channel, target, msg_to_send);
	}
	else{
		std::map<std::string, Channel>::iterator it_channel = channel_list.find(target);
		
		std::map<const int, Client>::iterator it_target = client_list.begin();
		while (it_target != client_list.end()){
			if (it_target->second.getNickname() == target)
				break;
			it_target++;
		}
		if (it_target == client_list.end() && it_channel == channel_list.end()){
			if (target == BOT_NAME)
				bot(server, client_fd, it_client->second, msg_to_send);
			else
				addToClientBuffer(server, client_fd, ERR_NOSUCHNICK(it_client->second.getNickname(), target));   
		}
		else{
			if (it_target == client_list.end()){
				if (isUserinChannel(it_client, it_channel) == true){
					target.insert(1, "#"); 
					broadcastToChannel(server, client_fd, it_client, it_channel, target, msg_to_send);
			}
			else
				addToClientBuffer(server, client_fd, ERR_NOSUCHNICK(it_client->second.getNickname(), target));
			}
			else
			addToClientBuffer(server, it_target->first, RPL_PRIVMSG(it_client->second.getNickname(), it_client->second.getUsername(), target, msg_to_send));    
		}
	}
}