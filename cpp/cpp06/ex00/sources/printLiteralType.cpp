#include "../headers/utils.hpp"
#include <iomanip> // Include for std::setprecision
#include <cstdlib>

bool is_printable(char c) { 
	return (c > 31 && c < 127);
}

void print_char_literal(const std::string &literal)
{
	std::cout << "char literal detected" << std::endl;
	
	int int_literal = static_cast<int>(literal[1]);
	float float_literal = static_cast<float>(literal[1]);
	double double_literal = static_cast<double>(literal[1]);

	if (!is_printable(literal[1]))
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: " << literal[1] << std::endl;

	std::cout << "int: " << int_literal << std::endl;
	std::cout << "float: " << float_literal << ".0f" << std::endl;
	std::cout << "double: " << double_literal << ".0" << std::endl;
}

void print_int_literal(const std::string &literal)
{
	std::cout << "int literal detected" << std::endl;

	int int_literal = atoi(literal.c_str());
	char char_literal = static_cast<char>(int_literal);
	float float_literal = static_cast<float>(atof(literal.c_str()));
	double double_literal = static_cast<double>(atof(literal.c_str()));

	if (is_printable(char_literal))
		std::cout << "char: " << char_literal << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;

	std::cout << "int: " << int_literal << std::endl;
	std::cout << "float: " << float_literal << ".0f" << std::endl;
	std::cout << "double: " << double_literal << ".0" << std::endl;
}

void print_float_literal(const std::string &literal)
{
	std::cout << "float literal detected" << std::endl;

	float float_literal = static_cast<float>(atof(literal.c_str()));
	int int_literal = static_cast<int>(float_literal);
	double double_literal = static_cast<double>(atof(literal.c_str()));

	std::cout << "char: ";
	if (is_printable(static_cast<char>(float_literal)))
		std::cout << static_cast<char>(float_literal) << std::endl;
	else
		std::cout << "Non displayable" << std::endl;

	std::cout << "int: " << int_literal << std::endl;

	if (float_literal == static_cast<int>(float_literal))
	    std::cout << std::fixed << std::setprecision(1); // Set precision as needed

	std::cout << "float: " << float_literal << "f" << std::endl;
	std::cout << "double: " << double_literal << std::endl;
}

void print_double_literal(const std::string &literal)
{
	std::cout << "double literal detected" << std::endl;

	double double_literal = atof(literal.c_str());
	int int_literal = static_cast<int>(double_literal);
	float float_literal = static_cast<float>(atof(literal.c_str()));

	std::cout << "char: ";
	if (is_printable(static_cast<char>(double_literal)))
		std::cout << static_cast<char>(double_literal) << std::endl;
	else
		std::cout << "Non displayable" << std::endl;

	std::cout << "int: " << int_literal << std::endl;

	if (double_literal == static_cast<int>(double_literal))
	    std::cout << std::fixed << std::setprecision(1); // Set precision as needed

	std::cout << "float: " << float_literal << "f" << std::endl;
	std::cout << "double: " << double_literal << std::endl;
}

void print_nan_literal()
{
	std::cout << "float: nanf" << std::endl;
	std::cout << "double: nan" << std::endl;
}

void print_inf_literal()
{
	std::cout << "float: +" << std::numeric_limits<float>::infinity()<<"f" << std::endl;
	std::cout << "double: +" << std::numeric_limits<double>::infinity() << std::endl;
}

void print_n_inf_literal()
{
	std::cout << "float: -" << std::numeric_limits<float>::infinity()<<"f" << std::endl;
	std::cout << "double: -" << std::numeric_limits<double>::infinity() << std::endl;
}

void print_char_int_impossible()
{
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
}

void print_pseudo_float_literal(const std::string &literal)
{	
	std::cout << "pseudo float literal detected" << std::endl;
	print_char_int_impossible();
	 if (literal == "-inff")
		print_n_inf_literal();
	else
		print_inf_literal();
}

void print_pseudo_double_literal(const std::string &literal)
{	
	std::cout << "pseudo double literal detected" << std::endl;
	print_char_int_impossible();
	if (literal == "nan")
		print_nan_literal();
	else if (literal == "-inf")
		print_n_inf_literal();
	else
		print_inf_literal();
}
