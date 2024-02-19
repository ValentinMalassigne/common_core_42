#include "../headers/Form.hpp"

Form::Form() :name("default form"),  isSigned(false), minGradeToSign(150), minGradeToExecute(150)
{}

Form::Form(const std::string c_name, const int c_minGradeToSign, const int c_minGradeToExecute) : name(c_name), isSigned(false), minGradeToSign(c_minGradeToSign), minGradeToExecute(c_minGradeToExecute)
{
	if (c_minGradeToExecute > 150 || c_minGradeToSign > 150)
	{
		throw Form::GradeTooLowException();
	} else if (c_minGradeToExecute < 1 || c_minGradeToSign < 1) {
		throw Form::GradeTooHighException();
	}
}

Form::Form(const Form& other) : name(other.name), minGradeToSign(other.minGradeToSign), minGradeToExecute(other.minGradeToExecute)
{
	*this = other;
}

Form::~Form()
{}

Form& Form::operator=(const Form& other)
{
	if (this != &other)
		isSigned = other.isSigned;
	return *this;
}

std::string Form::getName() const
{
	return name;
}

bool Form::getIsSigned() const
{
	return isSigned;
}

int Form::getMinGradeToSign() const
{
	return minGradeToSign;
}

int Form::getMinGradeToExecute() const
{
	return minGradeToExecute;
}

void Form::beSigned(Bureaucrat bureaucrat)
{
	if(bureaucrat.getGrade() > minGradeToSign)
		throw Form::GradeTooLowException();
	isSigned = true;
}

const char* Form::GradeTooLowException::what() const throw()
{
	return "Form Exception : Grade is too low";
}
 
const char* Form::GradeTooHighException::what() const throw()
{
	return "Form Exception : Grade is too high";
}

std::ostream& operator<<(std::ostream& os, const Form& form)
{
	os << form.getName() << ", form is signed : " << form.getIsSigned() << "\nminimum grade to sign : " << form.getMinGradeToSign() << "\n minimum grade to execute : " << form.getMinGradeToExecute() << std::endl;
	return os;
}