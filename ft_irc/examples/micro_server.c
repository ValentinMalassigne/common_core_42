//This is a test programm to see the connection from client 
//to server. We cannot send messages.

//To test, compile the micro_server.c and, in another terminal 
//connect to it with `nc localhost 2020`


#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define PORT "2020" //server's port
#define BACKLOG 10

int main(void) {
	//addrinfo is a structure used for storing information
	struct addrinfo hints;
    struct addrinfo *res;
    int socket_fd;
    int client_fd;
    int status;
    // sockaddr_storage is a structure that allows us to receive either
    // an IPv4 or an IPv6 address
    struct sockaddr_storage client_addr; 
    socklen_t addr_size;

    // Prepare the address and port for the server socket
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;        // IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;    // TCP
    hints.ai_flags = AI_PASSIVE;        // Automatically fills IP address

	//use to getaddress informations, here to retrieve the localhost, port number
	//and store the result in res.
	status = getaddrinfo(NULL, PORT, &hints, &res);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return (1);
    }

    // create socket, bind it and listen with it
    socket_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	// binds the socket to an address. 
    status = bind(socket_fd, res->ai_addr, res->ai_addrlen);
    if (status != 0) {
        fprintf(stderr, "bind: %s\n", strerror(errno));
        return (2);
    }
    listen(socket_fd, BACKLOG);

    // Accept incoming connection
    addr_size = sizeof client_addr;
    client_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &addr_size);
    if (client_fd == -1) {
        fprintf(stderr, "accept: %s\n", strerror(errno));
        return (3);
    }
    printf("New connection! Socket fd: %d, client fd: %d\n", socket_fd, client_fd);

    // We are ready to communicate with the client via the client_fd!

    return (0);
}