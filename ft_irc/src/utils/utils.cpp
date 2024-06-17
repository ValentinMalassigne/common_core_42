/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:22:52 by axel              #+#    #+#             */
/*   Updated: 2024/03/20 15:24:23 by cpothin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/ircserv.hpp"

/**
 * 
 * @brief Returns the client associated with the given client file descriptor.
 * 
 * This function takes a Server object pointer and a client file descriptor as input.
 * It retrieves the map of clients associated with the server, then searches for the client
 * with the specified file descriptor within the map. If the client is found, a pointer to
 * the client object is returned; otherwise, it returns NULL.
 * 
 * @param server - pointer to the server object.
 * @param client_fd - file descriptor of the client to retrieve
 * @return `client*` pointer to the Client object if found.
*/
Client*	getClient(Server *server, int const client_fd)
{
	std::map<const int, Client>&		client_list = server->getClients();
	std::map<const int, Client>::iterator it_client = client_list.find(client_fd);
	
	if (it_client == client_list.end())
		return (NULL);
	return (&it_client->second);
}

/**
 * @brief Sends a server reply message to a client.
 * 
 * This function takes a client file descriptor and a message string as input,
 * then sends the message to the client using the send() function. It also
 * prints a log message indicating the message sent to the client.
 * 
 * @param client_fd The file descriptor of the client to send the message to.
 * @param client_buffer The message to send to the client.
*/
void	sendServerRpl(int const client_fd, std::string client_buffer) {
	std::istringstream	buf(client_buffer);
	std::string			reply;

	send(client_fd, client_buffer.c_str(), client_buffer.size(), 0);
	while (getline(buf, reply)) {
		std::cout << ToColor("[Server] Message sent to client #", Colors::White())
			<< client_fd << ToColor(reply, Colors::Cyan()) << std::endl;
	}
}

/**
 * @brief Adds a message to the send buffer of a client.
 * 
 * This function retrieves the client object associated with the specified client file descriptor
 * from the server, and then sets the provided message as the send buffer of that client.
 * 
 * @param server A pointer to the Server object.
 * @param client_fd The file descriptor of the client.
 * @param reply The message to be added to the client's send buffer.
 */
void	addToClientBuffer(Server *server, int const client_fd, std::string reply){
	Client &client = retrieveClient(server, client_fd);

	client.setSendBuffer(reply);
}

/**
 * @brief Retrieves the client object associated with a client file descriptor.
 * 
 * This function retrieves the client object associated with the specified client file descriptor
 * from the server's client list.
 * 
 * @param server A pointer to the Server object.
 * @param client_fd The file descriptor of the client.
 * @return Client& A reference to the client object associated with the client file descriptor.
 */
Client &retrieveClient(Server *server, int const client_fd){
	std::map<const int, Client>&			client_list = server->getClients();
	std::map<const int, Client>::iterator	it_client = client_list.find(client_fd);

	Client	&client = it_client->second;
	return (client);
}

/**
 * @brief Sends registration messages to a client upon successful connection.
 * 
 * This function constructs and sends various registration messages to a client
 * upon successful connection, including welcome messages, server information,
 * server capabilities, and a message of the day (MOTD). If the MOTD file is
 * unavailable, it sends an error message indicating the absence of the MOTD.
 * 
 * @param server A pointer to the Server object.
 * @param client_fd The file descriptor of the client.
 * @param it An iterator pointing to the client in the server's client list.
 */
void	sendClientRegistration(Server *server, int const client_fd, 
	std::map<const int, Client>::iterator &it){
	addToClientBuffer(server, client_fd, RPL_WELCOME(user_id(it->second.getNickname(), 
		it->second.getUsername()), it->second.getNickname()));
	addToClientBuffer(server, client_fd, RPL_YOURHOST(it->second.getNickname(), "42_FT_IRC", "1,1"));
	addToClientBuffer(server, client_fd, RPL_CREATED(it->second.getNickname(), server->getDatetime()));
	addToClientBuffer(server, client_fd, RPL_MYINFO(it->second.getNickname(), "localhost", "1.1", "io", "kot", "k"));
	addToClientBuffer(server, client_fd, RPL_ISUPPORT(it->second.getNickname(), "CHANNEL_LEN=32 NICK_LEN=9 TOPIC_LEN=307"));

	std::ifstream	data;
	char			filepath[19] = "config/motd.config";

	data.open(filepath);
	if (!data){
		addToClientBuffer(server, client_fd, ERR_NOMOTD(it->second.getNickname()));
		return ;
	}
	else {
		std::string	modt_lines;
		std::string	buf;
		
		buf	= RPL_MOTDSTART(it->second.getNickname(), "42_FT_IRC (localhost)");
		while (getline(data, modt_lines)){
			buf += RPL_MOTD(it->second.getNickname(), modt_lines);
		}
		buf += RPL_ENDOFMOTD(it->second.getNickname());
		addToClientBuffer(server, client_fd, buf);
	}
	data.close();
}

/**
 * @brief Retrieves the symbol representing the channel mode.
 * 
 * This function retrieves the symbol representing the channel mode:
 * - "@" for secret channels
 * - "*" for private channels
 * - "=" for public channels
 * 
 * @param channel The Channel object representing the channel.
 * @return A string containing the symbol representing the channel mode.
 */
std::string	getSymbol(Channel &channel){
	std::string	symbol;

	if (channel.getMode().find('s') != std::string::npos)
		symbol += "@";
	else if (channel.getMode().find('p') != std::string::npos)
		symbol += "*";
	else
		symbol += "=";
	return (symbol);
}

/**
 * @brief Generates a list of channel members.
 * 
 * This function generates a list of members in the specified channel, excluding invisible users
 * if the client requesting the list is not a member of the channel.
 * 
 * @param client The nickname of the client requesting the list.
 * @param channel The Channel object representing the channel.
 * @return A string containing the list of members in the channel.
 */
std::string	getListOfMembers(std::string client, Channel &channel){
	std::map<std::string, Client>&			client_list	= channel.getClientList();
	std::map<std::string, Client>::iterator	it;
	std::string								nick;
	std::string								members_list;

	for (it = client_list.begin(); it != client_list.end(); it++)
	{
		nick.clear();
		nick = it->second.getNickname();
		if (it->second.getMode().find('i') != std::string::npos\
			&& channel.doesClientExist(client) == false)
				continue;
			
		if (channel.isOperator(nick) == true)
			members_list += "@";
		members_list += nick;
		members_list += " ";
	}
	if (members_list.size() >= 1 && members_list[members_list.size() - 1] == ' ')
		members_list.erase(members_list.end()-1);
	return (members_list);
}

/**
 * @brief Extracts the channel name from a message.
 * 
 * This function extracts the channel name from a message by searching for the first alphanumeric characters,
 * hyphens, or underscores, and then appending subsequent alphanumeric characters, hyphens, underscores, or digits
 * until a non-matching character is encountered.
 * 
 * @param msg_to_parse The message from which to extract the channel name.
 * @return A string containing the extracted channel name.
 */
std::string	getChannelName(std::string msg_to_parse){
	std::string channel_name;
	size_t i = 0;
	while (msg_to_parse[i] && (!isalpha(msg_to_parse[i]) && !isdigit(msg_to_parse[i]) && msg_to_parse[i] != '-' && msg_to_parse[i] != '_'))
		i++;
	while (msg_to_parse[i] && (isalpha(msg_to_parse[i]) || msg_to_parse[i] == '-' || msg_to_parse[i] == '_' || isdigit(msg_to_parse[i])))
		channel_name += msg_to_parse[i++];
	return (channel_name);
}
