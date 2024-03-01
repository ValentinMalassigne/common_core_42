#include "../headers/ScalarConverter.hpp"

ScalarConverter::ScalarConverter()
{
}

void ScalarConverter::convert(const std::string &literal)
{
	std::istringstream iss(literal);
	if (literal.find_first_of('\'') != std::string::npos)
	{
		// Char literal
		char c;

		if (iss >> c)
		{
			std::cout << "Char: " << c << std::endl;
		}
		else
		{
			std::cout << "Invalid char literal" << std::endl;
		}
	}
	else if (literal.find("f") != std::string::npos)
	{
		// Float literal
		float f;
		if (iss >> f)
		{
			std::cout << "Float: " << f << std::endl;
		}
		else
		{
			std::cout << "Invalid float literal" << std::endl;
		}
	}
	else
	{
		// Int or Double literal
		double d;
		if (iss >> d)
		{
			if (literal.find('.') != std::string::npos)
			{
				// Double literal
				std::cout << "Double: " << d << std::endl;
			}
			else
			{
				// Int literal
				int i = static_cast<int>(d);
				std::cout << "Int: " << i << std::endl;
			}
		}
		else
		{
			std::cout << "Invalid literal" << std::endl;
		}
	}
}