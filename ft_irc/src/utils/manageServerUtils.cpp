/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manageServerUtils.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:22:49 by axel              #+#    #+#             */
/*   Updated: 2024/03/25 19:05:12 by cpothin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/Server.hpp"

/**
 * @brief Accepts a new incoming connection on the specified listening socket.
 * 
 * This function accepts a new incoming connection on the specified listening socket,
 * which is typically bound to a port and set to listen for incoming connections.
 * It uses the accept() system call to accept the connection, retrieving the client's
 * address information and returning the new socket file descriptor for the connection.
 * 
 * @param listenSocket The file descriptor of the listening socket.
 * @return int The file descriptor of the new socket for the accepted connection.
*/
static int	acceptSocket(int listenSocket){
	sockaddr_in	client;
	socklen_t	addr_size = sizeof(sockaddr_in);
	return (accept(listenSocket, (sockaddr *)&client, &addr_size));
}

/**
 * @brief Notifies the client that the server has reached its maximum capacity.
 * 
 * This function sends an error message to the client indicating that the server
 * has reached its maximum capacity and cannot accept additional connections.
 * It prints an error message to the server's console and then closes the client socket.
 * 
 * @param client_socket The file descriptor of the client socket.
*/
static void	tooManyClients(int client_socket){
	std::cout << ToColor(ERR_SERV_FULL, Colors::Red()) << std::endl;
	send(client_socket, ERR_SERV_FULL, strlen(ERR_SERV_FULL) + 1, 0);
	close(client_socket);
}

/**
 * @brief Creates a new client connection and adds it to the poll list.
 * 
 * This function accepts a new incoming client connection on the server socket.
 * If the connection is accepted successfully and the maximum number of clients
 * has not been reached, the client socket is added to the list of file descriptors
 * to monitor for events using poll. If the maximum client limit is reached,
 * the function notifies the client that the server is full and closes the socket.
 * 
 * @param poll_fds The vector of pollfd structures representing active file descriptors.
 * @param new_pollfds The vector to host newly-created file descriptors.
 * @return int Returns SUCCESS if the client connection is successfully created,
 * CONTINUE if unable to accept the connection, or FAILURE if there are too many clients.
*/
int	Server::createClientConnexion(std::vector<pollfd>& poll_fds, std::vector<pollfd>& new_pollfds){
	int	client_socket = acceptSocket(_server_socket_fd);
	if (client_socket == -1) {
		std::cerr << ToColor("[Error] unable to accept", Colors::Red()) << std::endl;
		return (CONTINUE);
	}
	if (poll_fds.size() - 1 < MAX_CLIENT)
		addClient(client_socket, new_pollfds);
	else
		tooManyClients(client_socket);
	return (SUCCESS);
}


/**
 * @brief Prints a formatted message to the console for a given client socket.
 * 
 * This function prints a formatted message to the console based on the provided type
 * (e.g., "Error", "Info", "Warning") and the associated client socket. If a message
 * is provided, it is printed in the specified color using ToColor(). This function is
 * typically used for logging messages related to client interactions.
 * 
 * @param type The type of message to print (e.g., "Error", "Info", "Warning").
 * @param client_socket The file descriptor of the client socket.
 * @param message The message to print (optional).
*/
static void	print(std::string type, int client_socket, char *message){
	if (message)
		std::cout << std::endl << type << client_socket << ": " << ToColor(message, Colors::RoyalBlue());
}

/**
 * @brief Handles incoming data from an existing client connection.
 * 
 * This function receives data from an existing client connection represented by the
 * provided pollfd iterator. It retrieves the associated client object using getClient(),
 * reads incoming data from the client socket using recv(), and processes the received
 * message. If an error occurs during reception or if the client disconnects, it removes
 * the client from the poll list and returns BREAK. Otherwise, it prints the received
 * message to the console, sets the client's read buffer, and checks if a complete message
 * has been received for further processing.
 * 
 * @param poll_fds The vector of pollfd structures representing active file descriptors.
 * @param it An iterator pointing to the pollfd structure of the existing client connection.
 * @return int Returns SUCCESS if data is successfully handled, or BREAK if an error occurs
 * or the client disconnects.
*/
int Server::handleExistingConnexion(std::vector<pollfd>& poll_fds, std::vector<pollfd>::iterator &it){
	Client	*client;
	client = getClient(this, it->fd);
	char	message[MSG_SIZE];
	int		read_count;

	memset(message, 0, sizeof(message));
	read_count = recv(it->fd, message, MSG_SIZE, 0);

	if (read_count <= FAILURE){
		std::cerr << ToColor("[Server] recv() failed", Colors::Red()) << std::endl;
		delClient(poll_fds, it, it->fd);
		return (BREAK);
	}
	else if (read_count == 0){
		std::cout << ToColor("[Server] A client just disconnected", Colors::Orange()) << std::endl;
		delClient(poll_fds, it, it->fd);
		return (BREAK);
	}
	else{
		print("[Client] Message received from client #", it->fd, message); //!if problem check HERE
		client->setReadBuffer(message);

		if (client->getReadBuffer().find("\r\n") != std::string::npos){
			try {
				parseMsg(it->fd, client->getReadBuffer());
				if (client->getReadBuffer().find("\r\n"))
					client->getReadBuffer().clear();
			}
			catch(const std::exception& e){
				std::cout << ToColor("[Server] caught exception: ", Colors::Red());
				std::cerr << ToColor(e.what(), Colors::Red()) << std::endl;
				if (client->isRegistrationDone() == true)
					client->setDeconnexionStatus(true);
				return (BREAK);
			}
		}
	}
	return (SUCCESS);
}

/**
 * @brief Handles the event when a client socket is ready for sending data.
 * 
 * This function retrieves the client associated with the given file descriptor,
 * clears the client's send buffer, and sends the buffered data to the client.
 * If the client is not found, an error message is printed to the console.
 * 
 * @param poll_fds The vector of pollfd structures representing active file descriptors.
 * @param it An iterator pointing to the pollfd structure of the client socket.
 * @param current_fd The file descriptor of the client socket.
 * @return int Returns SUCCESS if the event is handled successfully.
*/
int Server::handlePolloutEvent(std::vector<pollfd>& poll_fds, std::vector<pollfd>::iterator &it, const int current_fd){
	Client	*client = getClient(this, current_fd);
	if (!client)
		std::cout << ToColor("[Server] Could not manage to find a connexion to client.", Colors::Red()) << std::endl;
	else {
		sendServerRpl(current_fd, client->getSendBuffer());
		client->getSendBuffer().clear();
		if (client->getDeconnexionStatus() == true) {
			delClient(poll_fds, it, current_fd);
			return (BREAK);
		}
	}
	return (SUCCESS);
}

/**
 * @brief Handles a poll error event on a client socket.
 * 
 * This function checks if the error event occurred on the server's listening socket
 * or on a client socket. If the error event is on the listening socket, it prints
 * an error message and returns FAILURE. If the error event is on a client socket,
 * it removes the client from the poll list and returns BREAK.
 * 
 * @param poll_fds The vector of pollfd structures representing active file descriptors.
 * @param it An iterator pointing to the pollfd structure of the client socket.
 * @return int Returns FAILURE if the error is on the server socket, or BREAK if on a client socket.
*/
int Server::handlePollerEvent(std::vector<pollfd>& poll_fds, std::vector<pollfd>::iterator &it){
	if (it->fd == _server_socket_fd) {
		std::cerr << ToColor("[Error] listen socket error", Colors::Red()) << std::endl;
		return (FAILURE);
	}
	else {
		delClient(poll_fds, it, it->fd);
		return (BREAK);
	}
}