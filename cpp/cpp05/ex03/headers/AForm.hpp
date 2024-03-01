#pragma once

#include <iostream>
#include "Bureaucrat.hpp"

class Bureaucrat;

class AForm
{
public:
	AForm();
	AForm(const std::string c_name, const int c_minGradeToSign, const int c_minGradeToExecute);
	AForm(const AForm &other);
	~AForm();

	AForm &operator=(const AForm &other);

	std::string getName() const;
	bool getIsSigned() const;
	int getMinGradeToSign() const;
	int getMinGradeToExecute() const;
	void beSigned(Bureaucrat bureaucrat);
	virtual void execute(Bureaucrat const &executor) const = 0;

	class GradeTooLowException : public std::exception
	{
		virtual const char *what() const throw();
	};

	class GradeTooHighException : public std::exception
	{
		virtual const char *what() const throw();
	};

	class FormNotSignedException : public std::exception
	{
		virtual const char *what() const throw();
	};

private:
	const std::string name;
	bool isSigned;
	const int minGradeToSign;
	const int minGradeToExecute;
	std::string target;

protected:
	void setTarget(const std::string newTarget);
	const std::string getTarget() const;
};

std::ostream &operator<<(std::ostream &os, const AForm &AForm);
