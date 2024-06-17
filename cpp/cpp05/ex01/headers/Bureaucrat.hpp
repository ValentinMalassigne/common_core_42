#pragma once

#include <iostream>
#include "Form.hpp"

class Form;

class Bureaucrat {
public:
	Bureaucrat();
	Bureaucrat(const std::string& c_name, int c_grade);
	Bureaucrat(const Bureaucrat &other);
	~Bureaucrat();

	Bureaucrat& operator=(const Bureaucrat& other);

	std::string getName() const;
	int getGrade() const;
	void incrementGrade();
	void decrementGrade();
	void signForm(Form form) const ;

	class GradeTooLowException : public std::exception {
		virtual const char* what() const throw();
	};

	class GradeTooHighException : public std::exception {
		virtual const char* what() const throw();
	};

private:
	const std::string name;
	int grade;
};

std::ostream& operator<<(std::ostream& os, const Bureaucrat& bureaucrat);
