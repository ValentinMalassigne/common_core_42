#include "../headers/Bureaucrat.hpp"

Bureaucrat::Bureaucrat()
{
}

Bureaucrat::Bureaucrat(const std::string &c_name, int c_grade) : name(c_name)
{
	if (c_grade > 150)
	{
		throw Bureaucrat::GradeTooLowException();
	}
	else if (c_grade < 1)
	{
		throw Bureaucrat::GradeTooHighException();
	}
	grade = c_grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat &other) : name(other.name), grade(other.grade)
{
}

Bureaucrat::~Bureaucrat()
{
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other)
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

void Bureaucrat::signForm(AForm &form) const
{
	try
	{
		form.beSigned(*this);
	}
	catch (const std::exception &e)
	{
		std::cerr << name << " couldn't sign " << form.getName() << " because " << e.what() << '\n';
		return;
	}
	std::cout << name << " signed " << form.getName() << std::endl;
}

void Bureaucrat::executeForm(AForm const &form) const
{
	try
	{
		form.execute(*this);
	}
	catch (const std::exception &e)
	{
		std::cerr << name << " couldn't execute " << form.getName() << " because " << e.what() << '\n';
		return;
	}
	std::cout << name << " executed " << form.getName() << std::endl;
}

const char *Bureaucrat::GradeTooLowException::what(void) const throw()
{
	return "Bureaucrat Exception : Grade is too low";
}

const char *Bureaucrat::GradeTooHighException::what(void) const throw()
{
	return "Bureaucrat Exception : Grade is too high";
}

std::ostream &operator<<(std::ostream &os, const Bureaucrat &bureaucrat)
{
	os << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << std::endl;
	return os;
}
