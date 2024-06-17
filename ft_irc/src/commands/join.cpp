/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:36:44 by acharlot          #+#    #+#             */
/*   Updated: 2024/03/21 17:00:04 by cpothin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/ircserv.hpp"

/**
 * *Prototype for the command => `/join #channel`
*/

/**
 * @brief Adds a client to a channel.
 * 
 * This function checks if the client is already present in the specified channel.
 * If not, it adds the client to the channel's client list.
 * 
 * @param server A pointer to the server instance.
 * @param channelName The name of the channel.
 * @param client The client to be added to the channel.
 */
void	addClientToChannel(Server *server, std::string &channelName, Client &client){
	std::map<std::string, Channel>::iterator	it;
	it = server->getChannels().find(channelName);
	std::string client_nickname = client.getNickname();

	if (it->second.doesClientExist(client_nickname) == false)
		it->second.getClientList().insert(std::pair<std::string, Client>(client.getNickname(), client));
	else
		std::cout << ToColor("[Client] ", Colors::Yellow()) << ToColor(client.getNickname(), Colors::Yellow())
			<< ToColor(" already here", Colors::Yellow()) << std::endl; 
}

/**
 * @brief Adds a new channel to the server.
 * 
 * This function checks if the channel with the specified name already exists.
 * If not, it creates a new channel with the given name and adds it to the server's list of channels.
 * 
 * @param server A pointer to the server instance.
 * @param channelName The name of the channel to add.
 */
void	addChannel(Server *server, std::string const &channelName){
	std::map<std::string, Channel>::iterator	it = server->getChannels().find(channelName);
	if (it != server->getChannels().end()){
		std::cout << ToColor("[Channel] already exists.", Colors::Red()) << std::endl;
		return ;
	}
	Channel channel(channelName);
	server->getChannels().insert(std::pair<std::string, Channel>(channelName, channel));
}

/**
 * @brief Retrieves the key from the message to parse.
 * 
 * This function extracts the key from the end of the message to parse,
 * which is typically used for operations like joining password-protected channels.
 * It removes leading spaces and extracts characters until it encounters a comma (`,`),
 * an underscore (`_`), a hyphen (`-`), or alphanumeric characters, forming the key.
 * 
 * @param msg_to_parse The message to parse from which the key is retrieved.
 * @return The extracted key.
 */
std::string	retrieveKey(std::string msg_to_parse){
	std::string	key;
	key.clear();
	
	msg_to_parse = msg_to_parse.substr(msg_to_parse.find_last_of(" "), msg_to_parse.npos);
	if (msg_to_parse[0] == ' ')
		msg_to_parse.erase(0, 1);
		
	int	begin_pos = (msg_to_parse.find(",") == 0) ? msg_to_parse.find(",") + 1 : 0;
	
	while ( msg_to_parse[begin_pos] != ',' && msg_to_parse[begin_pos]){
		if (msg_to_parse[begin_pos] == '_' || msg_to_parse[begin_pos] == '-'
			|| isalpha(msg_to_parse[begin_pos]) || isdigit(msg_to_parse[begin_pos]))
			key += msg_to_parse[begin_pos];
		begin_pos++;
	}
	return (key);
}

/**
 * @brief Sends channel information to clients upon joining.
 * 
 * This function sends relevant information about the channel to all clients
 * upon a client joining the channel. It sends JOIN messages to notify clients
 * of the joining, the topic of the channel if it's not empty, a list of channel
 * members (NAMES), and an indication of the end of the list.
 * 
 * @param server The server instance.
 * @param channel The channel instance.
 * @param channel_name The name of the channel.
 * @param client The client who joined the channel.
 */
void		sendChanInfos(Server *server, Channel &channel, std::string channel_name, Client &client){
	std::string	nick		= client.getNickname();
	std::string username	= client.getUsername();
 	
	std::map<std::string, Client>::iterator member = channel.getClientList().begin();

	while (member != channel.getClientList().end()){
		addToClientBuffer(server, member->second.getClientFd(), RPL_JOIN(user_id(nick, username), channel_name));
		if (channel.getTopic().empty() == false)
			addToClientBuffer(server, member->second.getClientFd(), RPL_TOPIC(nick, channel_name, channel.getTopic()));
		
		std::string	list_of_members = getListOfMembers(nick, channel);
		std::string symbol			= getSymbol(channel);

		addToClientBuffer(server, member->second.getClientFd(), RPL_NAMREPLY(username, symbol, channel_name, list_of_members));
		addToClientBuffer(server, member->second.getClientFd(), RPL_ENDOFNAMES(username, channel_name));
		member++;
	}
}

/**
 * @brief Checks if the string contains at least one alphabetic character.
 * 
 * This function checks if the input string contains at least one alphabetic character.
 * It ignores leading spaces and considers only the first word of the string.
 * 
 * @param str The input string to be checked.
 * @return True if the string contains at least one alphabetic character, false otherwise.
 */
bool		containsAtLeastOneAlphaChar(std::string str){
	if (str[0] == ' ')
		str.erase(0, 1);
	if (str.find(" ") != str.npos)
		str = str.substr(0, str.find(" "));
	for (size_t i = 0; i < str.size(); i++){
		if (isalpha(str[i]))
			return (true);
	}
	return (false);
}

/**
 * @brief Handles the JOIN command to join a channel.
 * 
 * This function parses the JOIN command message to extract the channel name.
 * It checks if the channel exists, if it requires a key (password), if it's full, or if the user is banned.
 * If the conditions are met, the user is added to the channel and channel information is sent to all members.
 * 
 * @param server A pointer to the Server object.
 * @param client_fd The file descriptor of the client.
 * @param cmd_infos The parsed command information.
 */
void	join(Server *server, int const client_fd, s_cmd cmd_infos){
	Client		client = retrieveClient(server, client_fd);
	std::string	client_nickname = client.getNickname();
	std::string	channel_name;

	if (containsAtLeastOneAlphaChar(cmd_infos.message) == false)
		addToClientBuffer(server, client_fd, ERR_NEEDMOREPARAMS(client_nickname, cmd_infos.name));
	while (containsAtLeastOneAlphaChar(cmd_infos.message) == true){
		channel_name.clear();
		channel_name = getChannelName(cmd_infos.message);
		cmd_infos.message.erase(cmd_infos.message.find(channel_name), channel_name.length());

		std::map<std::string, Channel>&				channels = server->getChannels();
		std::map<std::string, Channel>::iterator	it = channels.find(channel_name);
		if (it == channels.end())
			addChannel(server, channel_name);
		else if (it->second.getMode().find('k') != std::string::npos){
			std::string	key = retrieveKey(cmd_infos.message);
			cmd_infos.message.erase(cmd_infos.message.find(key), key.length());
			if (key != it->second.getChannelPassword()){
				std::cout << "IM IN (normal behavior)" << std::endl << std::endl;
				std::cout << "server: " << server << std::endl << std::endl;
				std::cout << "client_fd: " << client_fd << std::endl << std::endl;
				addToClientBuffer(server, client_fd, ERR_BADCHANNELKEY(client_nickname, channel_name));
				continue ;
			}
		}

		std::map<std::string, Channel>::iterator it_chan = server->getChannels().find(channel_name);
		if (it_chan->second.getCapacityLimit() != -1 && (int)it_chan->second.getClientList().size() == it_chan->second.getCapacityLimit()){
			addToClientBuffer(server, client_fd, ERR_CHANNELISFULL(client_nickname, channel_name));
			continue ;
		}
		if (it_chan->second.getMode().find('i') != std::string::npos){
			if (it_chan->second.isInvited(client_nickname) == false){
				addToClientBuffer(server, client_fd, ERR_NOTINVITED(client_nickname, channel_name));
				continue ;
			}
			else{
				addClientToChannel(server, channel_name, client);
				sendChanInfos(server, it_chan->second, channel_name, client);
			}
		}
		
		else{
			addClientToChannel(server, channel_name, client);
			if (it_chan->second.getOperators().empty())
				it_chan->second.addFirstOperator(client.getNickname());
			sendChanInfos(server, it_chan->second, channel_name, client);
		}
	}
}