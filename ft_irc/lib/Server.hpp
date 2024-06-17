/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:22:18 by axel              #+#    #+#             */
/*   Updated: 2024/02/16 10:47:35 by axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

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
struct server_op
{
	std::string	name;
	std::string	host;
	std::string	password;
};

struct s_cmd;

class Client;
class Channel;
class Server {
	private:
		struct addrinfo					_hints;
		struct addrinfo 				*_servinfo;
		int								_server_socket_fd;
		std::map<const int, Client>		_clients;
		std::map<std::string, Channel>	_channels;
		std::string						_port;
		std::string						_password;
		std::string						_datetime;
		std::vector<server_op>			_irc_operators;
		std::string						_motd;
	public:
		Server(std::string port, std::string password, struct tm *timeinfo);
		~Server(void);
		
		//Server.cpp
		std::map<const int, Client>&	getClients();
		std::string						getPort() const;
		std::string						getPassword() const;
		std::string						getDatetime() const;
		void							setDatetime(struct tm *timeinfo);
		std::map<std::string, Channel>&	getChannels();
		std::vector<server_op>&			getIRCOperators();
		std::string						getMotd() const;
		void							setPassword(std::string new_pwd);
		void							setMotd(std::string buffer);
		void							setHints(void);

		int								launchServer(void);
		int								fillInfos(char *port);
		void 							addClient(int client_socket, std::vector<pollfd> &poll_fds);
		void							delClient(std::vector<pollfd> &poll_fds, std::vector<pollfd>::iterator &it, int current_fd);
		void							addChannel(std::string &channelName);
		void							addClientToChannel(std::string &channelName, Client &client);
		int								readFromConfigFile(char *filename);
		bool							isChannel(std::string &channelName);
		//manageServerLoop
		int								manageServerLoop(void);
		
		//manageServerUtils
		int								createClientConnexion(std::vector<pollfd>& poll_fds, std::vector<pollfd>& new_pollfds);
		int 							handleExistingConnexion(std::vector<pollfd>& poll_fds, std::vector<pollfd>::iterator &it);
		int 							handlePolloutEvent(std::vector<pollfd>& poll_fds, std::vector<pollfd>::iterator &it, const int current_fd);
		int 							handlePollerEvent(std::vector<pollfd>& poll_fds, std::vector<pollfd>::iterator &it);

		//parsing
		void							fillClients(std::map<const int, Client> &client_lists, int client_fd, std::string cmd);
		void							execCommand(int const client_fd, std::string cmd_line);
		void							parseMsg(int const client_fd, std::string message);

		//Exception
		class InvalidClientException : public std::exception{
			public:
					const char *what(void) const throw();
	};
	
};

/****************************************************************
* 							FUNCTIONS							*
*****************************************************************/


#endif