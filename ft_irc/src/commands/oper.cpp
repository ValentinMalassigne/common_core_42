/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlot <acharlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:34:33 by acharlot          #+#    #+#             */
/*   Updated: 2024/02/19 15:34:34 by acharlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/ircserv.hpp"

/**
 * 
 * *Prototype for the command => `/oper` if the name is one of the operators.
*/

/**
 * @brief Checks if a name is valid by comparing it with a list of server operators.
 * 
 * This function iterates through the list of server operators and checks if the provided name
 * matches any of the operator names. If a match is found, it returns true indicating that
 * the name is valid, otherwise it returns false.
 * 
 * @param server Pointer to the server object.
 * @param name The name to check for validity.
 * @return true if the name is valid, false otherwise.
 */
static bool			isNameValid(Server *server, std::string name)
{
	std::vector<server_op>&				operators = server->getIRCOperators();
	std::vector<server_op>::iterator	op;

	for (op = operators.begin(); op != operators.end(); op++){
		if (op->name == name)
			return (true);
	}
	return (false);
}

/**
 * @brief Checks if a password is valid for a given server operator name.
 * 
 * This function searches for the provided name in the list of server operators.
 * If the name is found, it compares the associated password with the provided password.
 * If the passwords match, it returns true indicating that the password is valid, otherwise
 * it returns false.
 * 
 * @param server Pointer to the server object.
 * @param password The password to check.
 * @param name The server operator name.
 * @return true if the password is valid for the given name, false otherwise.
 */
static bool			isPasswordValid(Server *server, std::string password, std::string name)
{
	std::vector<server_op>&				operators = server->getIRCOperators();
	std::vector<server_op>::iterator	op;

	for (op = operators.begin(); op != operators.end(); op++)
		if (op->name == name)
			break;

	return (op->password == password ? true : false);
}

/**
 * @brief Extracts the name from a message.
 * 
 * This function extracts the name from the provided message by parsing
 * the message and retrieving the substring between the first and last space.
 * 
 * @param msg_to_parse The message to parse.
 * @return The extracted name.
 */
static std::string	getName(std::string msg_to_parse)
{
	std::string name;

	name.clear();
	if (msg_to_parse.empty() == false || msg_to_parse.find(" ") != msg_to_parse.npos){
		name.insert(0, msg_to_parse, 1,\
					msg_to_parse.find_last_of(" ") - 1);
	}
	return (name);
}

/**
 * @brief Extracts the password from a message.
 * 
 * This function extracts the password from the provided message by parsing
 * the message and retrieving the substring after the last space.
 * 
 * @param msg_to_parse The message to parse.
 * @return The extracted password.
 */
static std::string	getPassword(std::string msg_to_parse)
{
	std::string password;

	password.clear();
	if (msg_to_parse.empty() == false || msg_to_parse.find(" ") != msg_to_parse.npos){
		password.insert(0, msg_to_parse,\
					msg_to_parse.find_last_of(" ") + 1,\
					msg_to_parse.size() - 1);
	}
	return (password);
}

/**
 * @brief Handles the OPER command for granting operator privileges to a client.
 * 
 * This function extracts the name and password from the message and performs
 * checks to ensure that both are provided and valid. If the name is not found
 * in the list of server operators, an error message is sent to the client.
 * If the password does not match the one associated with the name, an error
 * message is sent to the client. Otherwise, operator privileges are granted
 * to the client, and a success message is sent.
 * 
 * @param server Pointer to the server object.
 * @param client_fd File descriptor of the client.
 * @param cmd_infos Structure containing command information.
 */
void oper(Server *server, int const client_fd, s_cmd cmd_infos){
	Client&		client		= retrieveClient(server, client_fd);
	std::string name		= getName(cmd_infos.message);
	std::string password	= getPassword(cmd_infos.message);

	if (name.empty() || password.empty()){
		addToClientBuffer(server, client_fd, ERR_NEEDMOREPARAMS(client.getNickname(), cmd_infos.name));
	}
	else if (isNameValid(server, name) == false){
		addToClientBuffer(server, client_fd, ERR_NOOPERHOST(client.getNickname()));
	}
	else if (isPasswordValid(server, password, name) == false)	{
		addToClientBuffer(server, client_fd, ERR_PASSWDMISMATCH(client.getNickname()));
	}
	else{
		addToClientBuffer(server, client_fd, RPL_YOUREOPER(client.getNickname()));
		client.addMode("o");
		addToClientBuffer(server, client_fd, MODE_USERMSG(client.getNickname(), "+o"));
	}
}