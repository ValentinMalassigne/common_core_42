/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manageServerLoop.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:22:42 by axel              #+#    #+#             */
/*   Updated: 2024/03/25 19:04:58 by cpothin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/ircserv.hpp"

bool	server_shutdown;

/**
 * @brief Manages the server's main loop using poll for event handling.
 * 
 * This function initializes a vector of pollfd structures with the server's file descriptor,
 * sets up the poll events to wait for input data, and enters a loop waiting for events
 * on the file descriptors using poll() to handles incoming data from clients.
 * It dynamically updates the list of file descriptors to watch based on new connections.
 * The loop breaks when server_shutdown is true or when an interrupt signal is received.
 * 
 * @return `FAILURE` or `SUCCESS` depending on the result.
*/
int Server::manageServerLoop(){
	std::vector<pollfd> poll_fds;
	pollfd server_poll_fd;

	server_poll_fd.fd = _server_socket_fd;
	server_poll_fd.events = POLLIN;

	poll_fds.push_back(server_poll_fd);

	while (server_shutdown == false){
		std::vector<pollfd> new_pollfds; 

		if (poll((pollfd *)&poll_fds[0], (unsigned int)poll_fds.size(), -1) <= SUCCESS){
			if (errno == EINTR)
				break ;
			std::cerr << ToColor("[Server] Poll error", Colors::Red()) << std::endl;
			throw ;
		}

		std::vector<pollfd>::iterator it = poll_fds.begin();
		while (it != poll_fds.end()){
			if (it->revents & POLLIN){
				if (it->fd == _server_socket_fd){
					if (this->createClientConnexion(poll_fds, new_pollfds) == CONTINUE)
						continue;
				}
				else{
					if (this->handleExistingConnexion(poll_fds, it) == BREAK)
						break ;
				}
			}
			else if (it->revents & POLLOUT){
				if (handlePolloutEvent(poll_fds, it, it->fd) == BREAK)
					break;
			}
			else if (it->revents & POLLERR){
				if (handlePollerEvent(poll_fds, it) == BREAK)
					break ;
				else
					return (FAILURE);
			}
			it++;
		}
		poll_fds.insert(poll_fds.end(), new_pollfds.begin(), new_pollfds.end());
	}

	return (SUCCESS);
}