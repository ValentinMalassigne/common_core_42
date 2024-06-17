#include <iostream>
#include "../headers/Bureaucrat.hpp"
#include "../headers/ShrubberyCreationForm.hpp"
#include "../headers/RobotomyRequestForm.hpp"
#include "../headers/PresidentialPardonForm.hpp"
#include "../headers/AForm.hpp"
#include "../headers/Intern.hpp"

int main()
{
	try
	{
		Intern someRandomIntern;
		AForm *rrf;
		rrf = someRandomIntern.makeForm("robotomy request", "Bender");

		if (!rrf)
			return 0;

		Bureaucrat bureaucrat("Jean", 150);

		std::cout << "form name : " << rrf->getName() << std::endl;

		bureaucrat.signForm(*rrf);
		bureaucrat.executeForm(*rrf);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << '\n';
		return 0;
	}
	return 0;
}
