/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharlot <acharlot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:36:20 by acharlot          #+#    #+#             */
/*   Updated: 2024/02/27 15:19:02 by acharlot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/ircserv.hpp"

/**
 * *Prototype for the command => `/mode #channel +option`
*/

/**
 * @brief Fills mode information structure from a command string.
 * 
 * This function extracts mode information from a command string and fills a mode information structure.
 * 
 * @param mode_infos The s_mode structure to fill with mode information.
 * @param command The command string containing mode information.
 */
static void	fillModeInfos(s_mode &mode_infos, std::string command){
	size_t	pos;

	pos = command.find(" ");
	if (pos == std::string::npos){
		mode_infos.target = command.substr(0);
		return ;
	}
	else {
		mode_infos.target = command.substr(0, pos);
		command.erase(0, pos + 1);
	}

	pos = command.find(" ");
	if (pos == std::string::npos){
		mode_infos.mode = command.substr(0);
		return ;
	}
	else {
		mode_infos.mode = command.substr(0, pos);
		command.erase(0, pos + 1);
	}

	mode_infos.params = command.substr(0);
}

/**
 * @brief Changes the mode of a channel.
 * 
 * This function changes the mode of a channel based on the mode information provided.
 * 
 * @param server Pointer to the Server object.
 * @param mode_infos Mode information structure containing target, mode, and parameters.
 * @param client_fd File descriptor of the client initiating the mode change.
 */
static void	changeChannelMode(Server *server,s_mode mode_infos, int const client_fd)
{
	std::map<const int, Client>::iterator it_client = server->getClients().find(client_fd);
	std::map<std::string, Channel>::iterator it_channel_target = server->getChannels().find(mode_infos.target);

	(void)it_client;
	(void)it_channel_target;

	std::vector<std::string> vector_modes;
	for (int i = 1; mode_infos.mode[i] != '\0'; i++){
		if (mode_infos.mode[i] == '+' || mode_infos.mode[i] == '-'){
			vector_modes.push_back(mode_infos.mode.substr(0, i));
			mode_infos.mode.erase(0, i);
			i = 0;
		}
	}
	vector_modes.push_back(mode_infos.mode.substr(0));
	for (std::vector<std::string>::iterator it = vector_modes.begin(); it != vector_modes.end(); it++){
		std::string str = *it;
		std::string datas[4];
		datas[0] = it_client->second.getNickname();
		datas[1] = mode_infos.target;
		datas[2] = str;
		datas[3] = mode_infos.params;
		if (str.find("i") != std::string::npos)
			inviteOnlyMode(server, datas, client_fd);
		if (str.find("k") != std::string::npos)
			keyChannelMode(server, mode_infos, client_fd, str);
		if (str.find("o") != std::string::npos)
			operatorChannelMode(server, mode_infos, client_fd, str);
		if (str.find("l") != std::string::npos)
			limitChannelMode(server, datas, client_fd);
		if (str.find("t") != std::string::npos)
			topicChannelMode(server, mode_infos, client_fd, str);
	}
}

/**
 * @brief Handles mode changes for a channel.
 * 
 * This function handles mode changes for a specific channel based on the mode information provided.
 * 
 * @param server Pointer to the Server object.
 * @param mode_infos Mode information structure containing target, mode, and parameters.
 * @param client_fd File descriptor of the client initiating the mode change.
 */
static void	modeForChannel(Server *server, s_mode mode_infos, int const client_fd)
{
	std::map<const int, Client>::iterator it_client = server->getClients().find(client_fd);

	mode_infos.target.erase(0,1);

	std::map<std::string, Channel>::iterator it_channel_target = server->getChannels().find(mode_infos.target);
	if (it_channel_target == server->getChannels().end())
	{
		addToClientBuffer(server, client_fd, ERR_NOSUCHCHANNEL(it_client->second.getNickname(), mode_infos.target));
		return ;
	}

	if (mode_infos.mode.empty() == true){
		if (it_channel_target->second.getClientList().find(it_client->second.getNickname()) != it_channel_target->second.getClientList().end() \
		&& it_channel_target->second.getChannelPassword().empty() == false)
			addToClientBuffer(server, client_fd, RPL_CHANNELMODEISWITHKEY(it_client->second.getNickname(), mode_infos.target, it_channel_target->second.getMode(), it_channel_target->second.getChannelPassword()));
		else
			addToClientBuffer(server, client_fd, RPL_CHANNELMODEIS(it_client->second.getNickname(), mode_infos.target, it_channel_target->second.getMode()));
		return ;
	}

	std::vector<std::string>::iterator it;
	for (it = it_channel_target->second.getOperators().begin(); it != it_channel_target->second.getOperators().end(); it++){
		if (*it == it_client->second.getNickname())
			break;
	}
	if (it == it_channel_target->second.getOperators().end()){
		addToClientBuffer(server, client_fd, ERR_CHANOPRIVSNEEDED(it_client->second.getNickname(), mode_infos.target));
		return ;
	}
	if (mode_infos.mode[0] == '+' || mode_infos.mode[0] == '-')
		changeChannelMode(server, mode_infos, client_fd);
}

/**
 * @brief Handles mode changes for a user.
 * 
 * This function handles mode changes for a specific user based on the mode information provided.
 * 
 * @param server Pointer to the Server object.
 * @param mode_infos Mode information structure containing target, mode, and parameters.
 * @param client_fd File descriptor of the client initiating the mode change.
 */
static void	modeForUser(Server *server, s_mode mode_infos, int const client_fd){
	std::map<const int, Client>::iterator it_client = server->getClients().find(client_fd);
	std::map<const int, Client>::iterator it_user_target = server->getClients().begin();

	while (it_user_target != server->getClients().end()){
		if (it_user_target->second.getNickname() == mode_infos.target)
			break;
		it_user_target++;
	}
	if (it_user_target == server->getClients().end()){
		addToClientBuffer(server, client_fd, ERR_NOSUCHNICK(it_client->second.getNickname(), mode_infos.target));
		return ;
	}

	if (it_user_target->second.getNickname() != it_client->second.getNickname()){
		addToClientBuffer(server, client_fd, ERR_USERSDONTMATCH(it_client->second.getNickname()));
		return ;
	}

	if (mode_infos.mode.empty() == true)
		addToClientBuffer(server, client_fd, RPL_UMODEIS(it_client->second.getNickname(), it_client->second.getMode()));
	
	if (mode_infos.mode[0] == '+' || mode_infos.mode[0] == '-'){
		std::string::iterator pos = mode_infos.mode.begin();
		while (pos != mode_infos.mode.end()){
			if (*pos == '+'){
				pos++;
				while (*pos != '+' && *pos != '-' && pos != mode_infos.mode.end()){
					if (*pos == 'i'){
						if (it_user_target->second.getMode().find("i") == std::string::npos){
							it_user_target->second.addMode("i");
							addToClientBuffer(server, client_fd, MODE_USERMSG(it_client->second.getNickname(), "+i"));
						}
					}
					pos++;
				}
			}
			if (*pos == '-'){
				pos++;
				while (*pos != '+' && *pos != '-' && pos != mode_infos.mode.end()){
					if (*pos == 'i'){
						if (it_user_target->second.getMode().find("i") != std::string::npos){
							it_user_target->second.removeMode("i");
							addToClientBuffer(server, client_fd, MODE_USERMSG(it_client->second.getNickname(), "-i"));
						}
					}
					if (*pos == 'o'){
						if (it_user_target->second.getMode().find("o") != std::string::npos){
							it_user_target->second.removeMode("o");
							addToClientBuffer(server, client_fd, MODE_USERMSG(it_client->second.getNickname(), "-o"));
						}
					}
					pos++;
				}
			}
		}
		if (mode_infos.mode.find("O") != std::string::npos || mode_infos.mode.find("r") != std::string::npos || mode_infos.mode.find("w") != std::string::npos)
			addToClientBuffer(server, client_fd, ERR_UMODEUNKNOWNFLAG(it_client->second.getNickname()));
	}
}

/**
 * @brief Handles mode changes for a user or a channel.
 * 
 * This function determines whether the mode change is intended for a channel or a user,
 * and then delegates the mode handling accordingly.
 * 
 * @param server Pointer to the Server object.
 * @param client_fd File descriptor of the client initiating the mode change.
 * @param cmd_infos Command information structure containing mode change details.
 */
void	modeFunction(Server *server, int const client_fd, s_cmd cmd_infos){
	s_mode	mode_infos;
	
	cmd_infos.message.erase(0,1);
	fillModeInfos(mode_infos, cmd_infos.message);

	if (mode_infos.target[0] == '#')
		modeForChannel(server, mode_infos, client_fd);
	else{
		modeForUser(server, mode_infos, client_fd);
	}
}