#ifndef COMMAND_HPP
# define COMMAND_HPP

/****************************************************************
* 							LIBRAIRIES							*
*****************************************************************/

# include "ircserv.hpp"

/****************************************************************
* 							LIBRAIRIES							*
*****************************************************************/
# define VALID_LEN 14


/****************************************************************
* 							CLASSES								*
*****************************************************************/

class Server;

struct	s_cmd
{
	std::string prefix;
	std::string name;
	std::string message;
};

struct s_mode
{
	std::string	target;
	std::string	mode;
	std::string	params;
};

/****************************************************************
* 							FUNCTIONS							*
*****************************************************************/

int		parseCommand(std::string cmd_line, s_cmd &cmd_infos);
void	invite(Server *server, int const client_fd, s_cmd cmd_infos);
void	join(Server *server, int const client_fd, s_cmd cmd_infos);
void	nick(Server *server, int const client_fd, s_cmd cmd_infos);
int		pass(Server *server, int const client_fd, s_cmd cmd_infos);
void	kick(Server *server, int const client_fd, s_cmd cmd_infos);
void	kill(Server *server, int const client_fd, s_cmd cmd_infos);
void	list(Server *server, int const client_fd, s_cmd cmd_infos);
void	modeFunction(Server *server, int const client_fd, s_cmd cmd_infos);
void	notice(Server *server, int const client_fd, s_cmd cmd_infos);
void	bot(Server *server, int const client_fd, Client &client, std::string bot_cmd);
void	motd(Server *server, int const client_fd, s_cmd cmd_infos);
void	names(Server *server, int const client_fd, s_cmd cmd_infos);
void oper(Server *server, int const client_fd, s_cmd cmd_infos);
void				part(Server *server, int const client_fd, s_cmd cmd_infos);
int	ping(Server *server, int const client_fd, s_cmd &cmd);
void	privmsg(Server *server, int const client_fd, s_cmd cmd_infos);
void		quit(Server *server, int const client_fd, s_cmd cmd_infos);
void	topic(Server *server, int const client_fd, s_cmd cmd_infos);
void	user(Server *server, int const client_fd, s_cmd cmd_infos);

#endif