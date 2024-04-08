/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:22:39 by axel              #+#    #+#             */
/*   Updated: 2024/03/21 11:40:32 by cpothin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/ircserv.hpp"

/**
 * @brief Signal handler function for catching interrupt signals.
 * 
 * This function is called when an interrupt signal (e.g., SIGINT) is received.
 * It hides the "^C" character sequence in the terminal by moving the cursor
 * two positions to the left ("\033[2D") and sets the server_shutdown flag to true.
 * 
 * @param signal The signal number (unused).
*/
static void	signal_handler(int signal){
	(void)signal;
	std::cout << "\033[2D"; //hide the ^C in the terminal
	server_shutdown = true;
}

/**
 * Main functions for the ircserv program.
*/
int	main(int argc, char **argv) {
	if (argc != 3){
		std::cerr << ToColor("[Usage] ./ircserv <port> <password>.", Colors::Red()) << std::endl;
		return (FAILURE);
	}
	else {
		time_t	rawtime;
		struct tm *timeinfo;

		time(&rawtime);
		timeinfo = localtime(&rawtime);
		
		srand(static_cast<unsigned int>(time(NULL)));
		signal(SIGINT, signal_handler);
		Server	server(argv[1], argv[2], timeinfo);

		char	filename[28] = "config/ServOperators.config";
		server.readFromConfigFile(filename);

		server.setHints();
		if (server.fillInfos(argv[1]) == FAILURE)
			return (FAILURE);
		server.launchServer();
		try {
			server.manageServerLoop();
		}
		catch(const std::exception& e){
			std::cerr << ToColor("Caught exception: ", Colors::Red())
				<< e.what() << std::endl;
		}
		return (SUCCESS);
	}
}
