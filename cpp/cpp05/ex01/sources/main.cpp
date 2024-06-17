#include <iostream>
#include "../headers/Bureaucrat.hpp"

int main()
{
	try
	{
		Bureaucrat bureaucrat("Jean", 100);
		Form form("hello form", 100, 100);

		bureaucrat.signForm(form);
	}
	catch(std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 0;
	}
	return 0;
}
