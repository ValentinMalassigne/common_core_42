/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:22:25 by axel              #+#    #+#             */
/*   Updated: 2024/03/23 15:44:00 by cpothin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/Channel.hpp"

							/*****************************
							 * CONSTRUCTOR & DESTRUCTOR *
							******************************/

Channel::Channel(std::string const &Name)
: _name(Name), _capacity_limit(-1){
	_clientList.clear();
	_list_invited.clear();
	_topic.clear();
}

Channel::~Channel(){

}

							/********************
							 * GETTER & SETTER *
							*********************/

std::string						&Channel::getName(){ return (_name);}
std::string						&Channel::getTopic(){ return (_topic);}
std::string						&Channel::getMode(){ return (_mode);}
std::string						&Channel::getChannelPassword(){ return (_channel_password);}
int								&Channel::getCapacityLimit(){ return (_capacity_limit);}
std::map<std::string, Client>	&Channel::getClientList(){ return (_clientList);}
std::vector<std::string>		&Channel::getVoicedUsers(){ return (_voiced_users);}
std::vector<std::string>		&Channel::getOperators(){ return (_operators);}
std::vector<std::string>		&Channel::getListInvited(){return (_list_invited);}

void	Channel::setTopic(std::string &newTopic){
	_topic = newTopic;
}

void	Channel::setChannelPassword(std::string &password){
	_channel_password = password;
}


void	Channel::setCapacityLimit(int limit){
	_capacity_limit = limit;
}

							/**********************
							 *		FUNCTIONS	 *
							***********************/

/**
 * @brief Checks if a client exists in the channel's client list.
 * 
 * This function determines whether a client with the specified name exists
 * in the channel's client list. If the client list is empty, it returns false.
 * Otherwise, it searches for the client using its name in the client list map.
 * If the client is found, it returns true; otherwise, it returns false.
 * 
 * @param clientName The name of the client to check for existence.
 * @return bool Returns true if the client exists, otherwise false.
 */
bool	Channel::doesClientExist(std::string &clientName){
	if (_clientList.size() == 0)
		return (false);
	else
	{
		std::map<std::string, Client>::iterator it;
		for (it = _clientList.begin(); it != _clientList.end(); it++){
			if (it->second.getNickname() == clientName)
				return true;
		}
	}
	return (false);
}

/**
 * @brief Removes a client from the channel.
 * 
 * This function removes a client from the channel's client list and also removes their operator status, if any.
 * 
 * @param clientName The name of the client to be removed.
 */
void	Channel::removeClientFromChannel(std::string &clientName){

	// std::map<std::string, Client>::iterator it;
	// for (it = _clientList.begin(); it != _clientList.end(); it++){
	// 	if (it->second.getNickname() == clientName)
	// 		this->_clientList.erase(it);
	// }
	std::map <std::string, Client>::iterator it = this->_clientList.find(clientName);
	if (it != _clientList.end())
		this->_clientList.erase(it);
	
	removeOperator(clientName); 
}

/**
 * @brief Adds a client to the channel's client list.
 * 
 * This function inserts a new client into the channel's client list using
 * the client's nickname as the key in the map.
 * 
 * @param client The client object to add to the channel.
 */
void	Channel::addClientToChannel(Client &client){
	_clientList.insert(std::pair<std::string, Client>(client.getNickname(), client));
}

/**
 * @brief Adds the first operator to the channel.
 * 
 * This function adds the specified operator name to the list of operators
 * in the channel only if the list is currently empty.
 * 
 * @param operatorName The name of the first operator to add.
 */
void	Channel::addFirstOperator(std::string &operatorName){
	if (_operators.empty())
		_operators.push_back(operatorName);
}

void printOperators(std::vector<std::string> &operators)
{
	std::vector<std::string>::iterator it;
	for (it = operators.begin(); it != operators.end(); it++){
		std::cout << *it << std::endl;
	}	
}

/**
 * @brief Removes an operator from the channel.
 * 
 * This function removes the specified operator name from the list of operators
 * in the channel if it exists.
 * 
 * @param operatorName The name of the operator to remove.
 */
void	Channel::removeOperator(std::string &operatorName){
	std::vector<std::string>::iterator it;
	for (it = _operators.begin(); it != _operators.end(); it++){
		if (*it == operatorName)
			_operators.erase(it);
	}
	printOperators(_operators);
}

void	Channel::renameOperator(std::string &operatorName, std::string &newName){
	std::vector<std::string>::iterator it;
	for (it = _operators.begin(); it != _operators.end(); it++){
		if (*it == operatorName)
		{
			*it = newName;
			break;
		}
	}
	printOperators(_operators);
}

/**
 * @brief Checks if a user is an operator in the channel.
 * 
 * This function iterates through the list of operators in the channel.
 * If the specified user is found in the list, it returns true indicating
 * that the user is an operator. If the list is empty or if the user is
 * not found, it returns false indicating that the user is not an operator.
 * 
 * @param operatorName The name of the user to check for operator status.
 * @return bool Returns true if the user is an operator, otherwise false.
 */
bool	Channel::isOperator(std::string &operatorName){
	std::vector<std::string>::iterator	user;
	if (_operators.empty())
		return (false);
	for (user = _operators.begin(); user != _operators.end(); user++){
		if (*user == operatorName)
			return (true);
	}
	return (false);
}

/**
 * @brief Adds a mode to the channel's mode string.
 * 
 * This function appends the specified mode to the channel's mode string.
 * If the mode string is currently empty, it initializes it with the mode
 * prefixed by a plus sign ('+'). If the mode string is not empty, it appends
 * the mode to the existing mode string.
 * 
 * @param mode The mode to add to the channel's mode string.
 */
void	Channel::addMode(std::string const mode){
	if (_mode.empty() == true)
		_mode = "+" + mode;
	else
		_mode += mode;
}

/**
 * @brief Removes a mode from the channel's mode string.
 * 
 * This function finds and removes the specified mode from the channel's mode string.
 * It searches for the mode in the mode string and erases the character at the found position.
 * 
 * @param mode The mode to remove from the channel's mode string.
 */
void	Channel::removeMode(std::string const mode){
	size_t pos = _mode.find(mode);
	_mode.erase(pos, 1);
}

/**
 * @brief Removes the channel's password.
 * 
 * This function clears the channel's password by emptying the channel_password string.
 */
void	Channel::removeChannelPassword(){
	_channel_password.clear();
}

/**
 * @brief Add the user to the invite list.
 * 
 * This function adds the user to an invite list.
 * 
 * @param nickname The nickname of the user to be invited.
 * 
*/
void Channel::addInvitedUser(const std::string &nickname){
	std::vector<std::string>::iterator	it;
	for (it = _list_invited.begin(); it != _list_invited.end(); it++){
		if (*it == nickname){
			std::cout << ToColor("[Channel] ", Colors::Red()) << nickname 
				<< ToColor(" is already invited on the channel ", Colors::Red()) 
				<< getName() << std::endl;
			return ;
		}
	}	
	_list_invited.push_back(nickname);
	std::cout << ToColor("[Channel] ", Colors::Red()) << nickname 
			<< ToColor(" is now invited on the channel ", Colors::Red())
			<< getName() << std::endl;
}

/**
 * @brief Check if a given nickname is invited to the channel.
 * 
 * This function checks if a given nickname is invited to the channel.
 * 
 * @param nickname The nickname of the user to be invited.
 * @return `true` or `false` depending if the user is invited or not.
*/
bool Channel::isInvited(std::string &nickname){
	std::vector<std::string>::iterator	it;
	if (_list_invited.empty() == true)
		return (false);
	for (it = _list_invited.begin(); it != _list_invited.end(); it++){
		if (*it == nickname)
			return (true);
	}
	return (false);
}