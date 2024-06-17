/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:22:00 by axel              #+#    #+#             */
/*   Updated: 2024/03/23 15:44:06 by cpothin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

/****************************************************************
* 							LIBRAIRIES							*
*****************************************************************/

# include "ircserv.hpp"

/****************************************************************
* 							MACRO								*
*****************************************************************/

/****************************************************************
* 							CLASSES								*
*****************************************************************/

class Client;
class Server;
class Channel
{
	private:
		std::map<std::string, Client>	_clientList;
		std::vector<std::string>		_operators;
		std::vector<std::string>		_voiced_users;
		std::string						_name;
		std::string						_operatorPassword;
		std::string						_topic;
		std::string						_mode;
		std::string						_channel_password;
		int								_capacity_limit;
		std::vector<std::string>		_list_invited;
	
	public:
		Channel(std::string const &Name);
		~Channel();
		
		std::string						&getName();
		std::string						&getTopic();
		std::string						&getMode();
		std::string						&getChannelPassword();
		int								&getCapacityLimit();
		std::map<std::string, Client>	&getClientList();
		std::vector<std::string>		&getVoicedUsers();
		std::vector<std::string>		&getOperators();
		std::vector<std::string>		&getListInvited();
		void							setTopic(std::string &newTopic);
		void							setChannelPassword(std::string &password);
		void							removeChannelPassword();
		void							setCapacityLimit(int limit);

		bool							doesClientExist(std::string &clientName);
		void							removeClientFromChannel(std::string &clientName);
		void							addClientToChannel(Client &client);
		void							addFirstOperator(std::string &operatorName);
		void							removeOperator(std::string &operatorName);
		void							renameOperator(std::string &operatorName, std::string &newName);
		bool							isOperator(std::string &operatorName);
		void							addMode(std::string const mode);
		void							removeMode(std::string const mode);
		void							addInvitedUser(const std::string& nickname);
		void 							removeFromInvitedUser(const std::string &nickname);
		bool							isInvited(std::string &nickname);
};


/****************************************************************
* 							FUNCTIONS							*
*****************************************************************/


#endif