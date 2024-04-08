/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:34:39 by acharlot          #+#    #+#             */
/*   Updated: 2024/03/22 09:47:13 by cpothin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/ircserv.hpp"

/**
 * *Prototype for the command => `/nick nickname`
*/

/**
 * @brief Retrieves the client's nickname from the given message.
 * 
 * This function parses the input message to extract the client's nickname.
 * If the message is empty, it returns an empty string.
 * If the message starts with a space, the leading space is removed.
 * If the message contains a space, the first word is considered the nickname.
 * If no nickname is found, an empty string is returned.
 * 
 * @param msg_to_parse The message to parse.
 * @return The extracted nickname.
 */
std::string	retrieveNickname(std::string msg_to_parse){
	std::string nickname;

	nickname.clear();
	if (msg_to_parse.empty())
		return (nickname);
	if (msg_to_parse.empty() == false && msg_to_parse[0] == ' ')
		msg_to_parse.erase(0, 1);
	if (msg_to_parse.empty() == false && msg_to_parse.find(' ')){
		char *str = const_cast<char *>(msg_to_parse.data());
		nickname = strtok(str, " ");
	}
	if (nickname.empty())
		nickname.clear();
	return (nickname);
}

/**
 * @brief Checks if a character is in the set of forbidden characters.
 * 
 * This function takes a character as input and checks if it belongs to
 * the set of forbidden characters, which includes space, comma, asterisk,
 * question mark, exclamation mark, at symbol, and period.
 * 
 * @param c The character to check.
 * @return true if the character is forbidden, false otherwise.
 */
static bool	isForbidden(char c){
	if (c == ' ' || c == ',' || c == '*' || c == '?' || c == '!'
		|| c == '@' || c == '.')
		return (true);
	else
		return (false);
}

/**
 * @brief Checks if a nickname contains invalid characters.
 * 
 * This function checks if the given nickname contains any invalid characters.
 * If the first character of the nickname is '$', ':', or '#', it is considered
 * invalid. Additionally, it iterates through each character of the nickname
 * and checks if it is a forbidden character using the isForbidden function.
 * 
 * @param nickname The nickname to check.
 * @return true if the nickname contains invalid characters, false otherwise.
 */
static bool	containsInvalidCharacters(std::string nickname){
	if (nickname[0] == '$' || nickname[0] == ':' || nickname[0] == '#')
		return (true);
	
	for (size_t i = 0; i < nickname.size(); i++){
			if (isForbidden(nickname[i]) == true)
				return (true);
	}
	return (false);			
}

/**
 * @brief Checks if a nickname is already used by another client.
 * 
 * This function iterates through the client list of the server and checks if
 * any client (except the one with the provided file descriptor) has the same
 * nickname as the new nickname provided. If a client with a matching nickname
 * is found, true is returned, indicating that the new nickname is already used.
 * 
 * @param server Pointer to the server object.
 * @param client_fd File descriptor of the client.
 * @param new_nickname The new nickname to check.
 * @return true if the nickname is already used, false otherwise.
 */
bool	isAlreadyUsed(Server *server, int client_fd, std::string new_nickname){
	std::map<const int, Client>&			client_list	= server->getClients();
	std::map<const int, Client>::iterator	client		= client_list.begin();

	while (client != client_list.end()){
		if (client->second.getClientFd() != client_fd \
			&& client->second.getNickname() == new_nickname)
			return (true);
		client++;
	}
	return (false);
}

/**
 * @brief Handles the NICK command for changing or setting a client's nickname.
 * 
 * This function extracts the nickname from the message received from the client
 * and retrieves the client object associated with the provided file descriptor.
 * If the client's registration is not completed, it sets the nickname, increments
 * the number of informational messages, and performs various checks on the nickname.
 * If the nickname is empty, an error message is sent to the client.
 * If the nickname contains invalid characters, an error message is sent to the client.
 * If the nickname is already used by another client, an error message is sent to the client.
 * Otherwise, if the client's registration is completed, it updates the client's old
 * nickname, sets the new nickname, and sends a success message to the client.
 * 
 * @param server Pointer to the server object.
 * @param client_fd File descriptor of the client.
 * @param cmd_infos Structure containing command information.
 */
void	nick(Server *server, int const client_fd, s_cmd cmd_infos){
	std::string nickname	= retrieveNickname(cmd_infos.message);
	Client&		client		= retrieveClient(server, client_fd);

	if (client.isRegistrationDone() == false){
		client.setNickname(nickname);
		client.setOldNickname(nickname);
		client.setNbInfo(+1);
	}

	if (nickname.empty()){
		addToClientBuffer(server, client_fd, ERR_NONICKNAMEGIVEN(client.getNickname()));
		if (client.isRegistrationDone() == false)
			client.setNbInfo(-1);
	} 
	else if (containsInvalidCharacters(nickname)){
		addToClientBuffer(server, client_fd,  ERR_ERRONEUSNICKNAME(client.getNickname(), nickname));
		if (client.isRegistrationDone() == false)
			client.setNbInfo(-1);
	} 
	else if (isAlreadyUsed(server, client_fd, nickname) == true){
			addToClientBuffer(server, client_fd, ERR_NICKNAMEINUSE(client.getNickname(), nickname));
		if (client.isRegistrationDone() == false)
			client.setNbInfo(-1);
	} else{
		
		if (client.isRegistrationDone() == true)
		{
			std::map<std::string, Channel>::iterator	it;
			for (it = server->getChannels().begin(); it != server->getChannels().end(); it++)
			{
				std::map<std::string, Client>::iterator it2;
				for (it2 = it->second.getClientList().begin(); it2 != it->second.getClientList().end(); it2++)
				{
					if (it2->second.getNickname() == client.getNickname())
					{
						std::string oldName = client.getNickname();
						it2->second.setNickname(nickname);
						it->second.renameOperator(oldName, nickname);
					}
					std::cout << "\tNickname:" << it2->second.getNickname() << std::endl << "\tOld nickname:" << it2->second.getOldNickname() << std::endl;
				}
			}
			client.setOldNickname(client.getNickname());
			client.setNickname(nickname);
			std::cout << "[Server] Nickname change registered. New nickname is now: " << client.getNickname() << std::endl;
		}
	}
	addToClientBuffer(server, client_fd, RPL_NICK(client.getOldNickname(), client.getUsername(), client.getNickname()));
}