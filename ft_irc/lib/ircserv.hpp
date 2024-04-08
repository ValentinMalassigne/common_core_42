/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:22:13 by axel              #+#    #+#             */
/*   Updated: 2024/03/21 11:45:01 by cpothin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERV_HPP
# define IRCSERV_HPP

/****************************************************************
* 							LIBRAIRIES							*
*****************************************************************/

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <cstring>
# include <cstdlib>
# include <iostream>
# include <vector>
# include <map>
# include <list>
# include <poll.h>
# include <unistd.h>
# include <sstream>
# include <fstream>
# include <csignal>
# include <string>
# include <cerrno>
# include <ctime>
# include <algorithm>

# include "Colors.hpp"
# include "Server.hpp"
# include "ErrorMessage.hpp"
# include "Client.hpp"
# include "Channel.hpp"
# include "Command.hpp"

/****************************************************************
* 							LIBRAIRIES							*
*****************************************************************/
# define FAILURE -1
# define SUCCESS 0
# define BREAK 2
# define CONTINUE 3
# define BACKLOG 10
# define MAX_CLIENT 12
# define MSG_SIZE 4096
# define BOT_NAME "raultbot"

extern bool	server_shutdown;
/****************************************************************
* 							CLASSES								*
*****************************************************************/

class Server;

struct Country
{
	std::string name;
	std::string capital;
	double size;
	long long population;
	std::string president;
};

/****************************************************************
* 							FUNCTIONS							*
*****************************************************************/

Client*		getClient(Server *server, int const client_fd);
void		sendServerRpl(int const client_fd, std::string client_buffer);
void		sendClientRegistration(Server *server, int const client_fd, std::map<const int, Client>::iterator &it);
void		addToClientBuffer(Server *server, int const client_fd, std::string reply);
Client		&retrieveClient(Server *server, int const client_fd);
void		sendClientRegistration(Server *server, int const client_fd, std::map<const int, Client>::iterator &it);
std::string	getSymbol(Channel &channel);
std::string	getListOfMembers(std::string client, Channel &channel);
std::string	getChannelName(std::string msg_to_parse);
std::string	getReason(std::string msg_to_parse);
void		broadcastToAllChannelMembers(Server *server, Channel &channel, std::string reply);

//MODE
void	inviteOnlyMode(Server *server, std::string datas[4], int const client_fd);
void	keyChannelMode(Server *server, s_mode mode_infos, int const client_fd, std::string mode_str);
void	limitChannelMode(Server *server, std::string datas[4], int const client_fd);
void	operatorChannelMode(Server *server, s_mode mode_infos, int const client_fd, std::string str);
void	topicChannelMode(Server *server, s_mode mode_infos, int const client_fd, std::string mode_str);

#endif