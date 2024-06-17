/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:22:04 by axel              #+#    #+#             */
/*   Updated: 2024/03/25 09:07:54 by cpothin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

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

enum QuestionType
{
	None,
	Capital,
	President,
	LargerArea,
	MostPopulated
};

typedef struct s_bot
{
	QuestionType questionType;
	std::string country1, country2;
	std::string president1, president2;
	std::string capital1, capital2;
	double area1, area2;
	int pop1, pop2;
	std::string answer;
	bool firstTime;
	s_bot() : questionType(None), country1(""), country2(""), president1(""), president2(""), capital1(""), capital2(""), area1(0.0), area2(0.0), pop1(0), pop2(0), answer(""), firstTime(false) {}
}				t_bot;


class Client {
	private:
		int				_client_fd;
		std::string		_readbuf;
		std::string		_sendbuf;
		bool			_to_deconnect;
		std::string		_nickname;
		std::string		_old_nickname;
		std::string 	_username;
		std::string		_realname;
		std::string		_mode;
		bool			_connexion_password;
		bool			_registrationDone;
		bool			_welcomeSent;
		bool			_hasAllInfo;
		int				_nbInfo;

	public:
		Client(int client_fd);
		~Client(void);
		
		t_bot			bot_question;
		int				getClientFd()const;
		std::string&	getSendBuffer();
		std::string&	getReadBuffer();
		std::string&	getNickname();
		std::string&	getOldNickname(); 
		std::string 	getUsername() const;
		std::string		getRealname() const;
		std::string&	getMode();
		bool&			getConnexionPassword();
		bool&			isRegistrationDone();
		bool&			isWelcomeSent();
		bool&			hasAllInfo();
		bool&			getDeconnexionStatus();
		int				getNbInfo() const;
		void			setReadBuffer(std::string const &buf);
		void			resetReadBuffer(std::string const &str);
		void			setSendBuffer(std::string const &buf);
		void			setDeconnexionStatus(bool status);
		void			setNickname(std::string const &nickname);
		void			setOldNickname(std::string const &nickname);
		void			setUsername(std::string const &username);
		void			setRealname(std::string const &realname);
		void			addMode(std::string const mode);
		void			removeMode(std::string const mode);
		void			setConnexionPassword(bool boolean);
		void			setRegistrationDone(bool boolean);
		void			setWelcomeSent(bool boolean);
		void			setHasAllInfo(bool boolean);
		void			setNbInfo(int n);

		int				isValid() const;
};

/****************************************************************
* 							FUNCTIONS							*
*****************************************************************/

#endif