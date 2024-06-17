#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat()
{}

Bureaucrat::Bureaucrat(const std::string& c_name, int c_grade) : name(c_name)
{
	if (c_grade > 150)
	{
		throw Bureaucrat::GradeTooLowException();
	} else if (c_grade < 1) {
		throw Bureaucrat::GradeTooHighException();
	}
	grade = c_grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat& other) : name(other.name), grade(other.grade)
{}

Bureaucrat::~Bureaucrat()
{}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other)
{
	if (this != &other)
	{
		grade = other.grade;
	}
	return *this;
}

std::string Bureaucrat::getName() const
{
	return name;
}

int Bureaucrat::getGrade() const
{
	return grade;
}

void Bureaucrat::incrementGrade()
{
	if (grade == 1)
	{
		throw Bureaucrat::GradeTooHighException();
	}
	grade--;
}

void Bureaucrat::decrementGrade()
{
	if (grade == 150)
	{
		throw Bureaucrat::GradeTooLowException();
	}
	grade++;
}

const char * Bureaucrat::GradeTooLowException::what(void) const throw()
{
	return "Grade is too low";
}

const char * Bureaucrat::GradeTooHighException::what(void) const throw()
{
	return "Grade is too high";
}

std::ostream& operator<<(std::ostream& os, const Bureaucrat& bureaucrat)
{
	os << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << std::endl;
	return os;
}
