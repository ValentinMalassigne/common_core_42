#include "../headers/AForm.hpp"

AForm::AForm() : name("default AForm"), isSigned(false), minGradeToSign(150), minGradeToExecute(150)
{
}

AForm::AForm(const std::string c_name, const int c_minGradeToSign, const int c_minGradeToExecute) : name(c_name), isSigned(false), minGradeToSign(c_minGradeToSign), minGradeToExecute(c_minGradeToExecute)
{
	if (c_minGradeToExecute > 150 || c_minGradeToSign > 150)
	{
		throw AForm::GradeTooLowException();
	}
	else if (c_minGradeToExecute < 1 || c_minGradeToSign < 1)
	{
		throw AForm::GradeTooHighException();
	}
}

AForm::AForm(const AForm &other) : name(other.name), minGradeToSign(other.minGradeToSign), minGradeToExecute(other.minGradeToExecute)
{
	*this = other;
}

AForm::~AForm()
{
}

AForm &AForm::operator=(const AForm &other)
{
	if (this != &other)
		isSigned = other.isSigned;
	return *this;
}

std::string AForm::getName() const
{
	return name;
}

bool AForm::getIsSigned() const
{
	return isSigned;
}

int AForm::getMinGradeToSign() const
{
	return minGradeToSign;
}

int AForm::getMinGradeToExecute() const
{
	return minGradeToExecute;
}

void AForm::beSigned(Bureaucrat bureaucrat)
{
	if (bureaucrat.getGrade() > minGradeToSign)
		throw AForm::GradeTooLowException();
	isSigned = true;
}

const char *AForm::GradeTooLowException::what() const throw()
{
	return "AForm Exception : Grade is too low";
}

const char *AForm::GradeTooHighException::what() const throw()
{
	return "AForm Exception : Grade is too high";
}

const char *AForm::FormNotSignedException::what() const throw()
{
	return "AForm Exception : Form is not signed";
}

void AForm::setTarget(const std::string newTarget)
{
	target = newTarget;
}

std::string AForm::getTarget() const
{
	return target;
}

std::ostream &operator<<(std::ostream &os, const AForm &aForm)
{
	os << aForm.getName() << ", AForm is signed : " << aForm.getIsSigned() << "\nminimum grade to sign : " << aForm.getMinGradeToSign() << "\n minimum grade to execute : " << aForm.getMinGradeToExecute() << std::endl;
	return os;
}