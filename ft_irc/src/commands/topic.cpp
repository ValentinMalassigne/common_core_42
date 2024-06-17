/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:34:01 by acharlot          #+#    #+#             */
/*   Updated: 2024/02/23 18:32:06 by axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/ircserv.hpp"

/**
 * *Need to be an operator to change it.
 * *Prototype for the command => `/topic #channel :Topic`
 * 
 * *For users to view
 * *Prototype for the command => `/topic`
*/

/**
 * @brief Finds the name of the channel mentioned in a message.
 * 
 * This function extracts the channel name from the provided message.
 * If the message does not contain a channel name, an empty string is returned.
 * 
 * @param msg_to_parse The message to parse.
 * @return The name of the channel mentioned in the message.
 */
std::string	findChannelName(std::string msg_to_parse){
	std::string channel_name;
	channel_name.clear();
	
	if (msg_to_parse.empty() || msg_to_parse.find("#") == msg_to_parse.npos)
		return (channel_name);
	else if (msg_to_parse.find(":") != msg_to_parse.npos){
		char *str = const_cast<char *>(msg_to_parse.data());
		channel_name = strtok(str, " ");
		channel_name.erase(channel_name.find("#"), 1);
	}
	else{
		size_t i = 0;
		while (msg_to_parse[i] && (!isalpha(msg_to_parse[i]) && !isdigit(msg_to_parse[i]) && msg_to_parse[i] != '-' && msg_to_parse[i] != '_'))
			i++;
		while (msg_to_parse[i] && (isalpha(msg_to_parse[i]) || msg_to_parse[i] == '-' || msg_to_parse[i] == '_' || isdigit(msg_to_parse[i])))
			channel_name += msg_to_parse[i++];
	}
	return (channel_name);
}

/**
 * @brief Finds the topic mentioned in a message.
 * 
 * This function extracts the topic from the provided message.
 * If the message does not contain a topic, an empty string is returned.
 * 
 * @param msg_to_parse The message to parse.
 * @return The topic mentioned in the message.
 */
std::string	findTopic(std::string msg_to_parse){
	std::string topic;

	if (msg_to_parse.empty() || msg_to_parse.find(":") == msg_to_parse.npos)
		topic.clear();
	else
		topic.append(msg_to_parse, msg_to_parse.find(":"), std::string::npos);
	return (topic);
}

/**
 * @brief Broadcasts a topic change to all members of a channel.
 * 
 * This function sends a topic change message to all members of the specified channel.
 * It iterates through the client list of the channel and sends the topic change message to each member.
 * 
 * @param server Pointer to the server object.
 * @param channel Reference to the channel object.
 * @param client Reference to the client object.
 * @param channel_name The name of the channel.
 * @param topic The new topic of the channel.
 */
static void	broadcastTopicToChannel(Server *server, Channel &channel, Client &client,
 std::string channel_name, std::string topic){
	std::map<std::string, Client>::iterator member = channel.getClientList().begin();
	std::string								client_nickname = client.getNickname();
	
	while (member != channel.getClientList().end()){
		addToClientBuffer(server, member->second.getClientFd(), RPL_TOPIC(client_nickname, channel_name, topic));
		member++;
	}
}

/**
 * @brief Handles the TOPIC command for setting or querying the topic of a channel.
 * 
 * This function parses the message to extract the channel name and topic.
 * If no channel name is provided, an error message is sent to the client.
 * If the channel does not exist, an error message is sent to the client.
 * If the client is not a member of the channel, an error message is sent.
 * If no topic is provided, the current topic of the channel is sent to the client.
 * If the client does not have sufficient privileges to set the topic, an error message is sent.
 * Otherwise, the topic is set and broadcasted to all members of the channel.
 * 
 * @param server Pointer to the server object.
 * @param client_fd File descriptor of the client.
 * @param cmd_infos Structure containing command information.
 */
void	topic(Server *server, int const client_fd, s_cmd cmd_infos){
	std::string channel_name;
	std::string	topic;
	
	Client&		client = retrieveClient(server, client_fd);
	std::string client_nickname = client.getNickname();

	channel_name = findChannelName(cmd_infos.message);
	if (channel_name.empty()){
		addToClientBuffer(server, client_fd, ERR_NEEDMOREPARAMS(client_nickname, cmd_infos.name));
		return ;
	}

	std::map<std::string, Channel>&			 channels = server->getChannels();
	std::map<std::string, Channel>::iterator channel = channels.find(channel_name);
	if (channel == channels.end()){
		addToClientBuffer(server, client_fd, ERR_NOSUCHCHANNEL(client_nickname, channel_name));
		return ;
	}
	if (channel->second.doesClientExist(client_nickname) == false){
		addToClientBuffer(server, client_fd, ERR_NOTONCHANNEL(client_nickname, channel_name));
		return ;
	}

	topic = findTopic(cmd_infos.message);
	std::cout << "[TOPIC] => " << topic << std::endl;
	
	if (topic.empty()){
		if (channel->second.getTopic().empty() == false)
			addToClientBuffer(server, client_fd, RPL_TOPIC(client_nickname, channel_name, channel->second.getTopic()));
		else
			addToClientBuffer(server, client_fd, RPL_NOTOPIC(client_nickname, channel_name));
	}
	else{
		if (channel->second.getMode().find('t') != std::string::npos
			&& channel->second.isOperator(client_nickname) == false)
			addToClientBuffer(server, client_fd, ERR_CHANOPRIVSNEEDED(client_nickname, channel_name));
		else{
			if (topic == ":")
				topic.clear();
			channel->second.setTopic(topic);
			broadcastTopicToChannel(server, channel->second, client, channel_name, topic);
		}
	}
}