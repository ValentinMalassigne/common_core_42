#include <iostream>
#include "../headers/Bureaucrat.hpp"
#include "../headers/ShrubberyCreationForm.hpp"
#include "../headers/RobotomyRequestForm.hpp"
#include "../headers/PresidentialPardonForm.hpp"

int main()
{
	try
	{
		Bureaucrat bureaucrat("Jean", 150);
		// ShrubberyCreationForm form("target1");
		// RobotomyRequestForm form("target1");
		PresidentialPardonForm form("target1");
		bureaucrat.signForm(form);
		bureaucrat.executeForm(form);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << '\n';
		return 0;
	}
	return 0;
}