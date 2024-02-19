#pragma once

#include <iostream>
#include "Bureaucrat.hpp"

class Bureaucrat;

class Form {
public:
	Form();
	Form(const std::string c_name, const int c_minGradeToSign, const int c_minGradeToExecute);
	Form(const Form &other);
	~Form();

	Form& operator=(const Form& other);

	std::string getName() const;
	bool getIsSigned() const ;
	int getMinGradeToSign() const ;
	int getMinGradeToExecute() const;
	void beSigned(Bureaucrat bureaucrat);

	class GradeTooLowException : public std::exception {
		virtual const char* what() const throw();
	};

	class GradeTooHighException : public std::exception {
		virtual const char* what() const throw();
	};

private:
	const std::string name;
	bool isSigned;
	const int minGradeToSign;
	const int minGradeToExecute;
};

std::ostream& operator<<(std::ostream& os, const Form& form);
