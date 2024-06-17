#include "Bureaucrat.hpp"
#include <iostream>

int main()
{
	try
	{
		Bureaucrat bureaucrat("Jean", 150);
		std::cout << bureaucrat;
		bureaucrat.decrementGrade();
	}
	catch(std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 0;
	}
	
	return 0;
}
