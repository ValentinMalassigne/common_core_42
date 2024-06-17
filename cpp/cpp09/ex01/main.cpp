#include "RPN.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: ./rpn \"expression\"" << std::endl;
		return 1;
	}

	try
	{
		std::cout << RPN::solve_expression(argv[1]) << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}