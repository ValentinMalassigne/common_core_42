#include "../headers/ScalarConverter.hpp"
#include "../headers/utils.hpp"
#include <iostream>

ScalarConverter::ScalarConverter()
{
}

ScalarConverter::ScalarConverter(const ScalarConverter &other)
{
	*this = other;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter &other)
{
	(void) other;
	return *this;
}

ScalarConverter::~ScalarConverter()
{}

//doit recevoir un string qui represente un "C++ literal"
//et doit l'output dans les types scalaires : char, int, float, double
void ScalarConverter::convert(const std::string &literal)
{
	switch (getType(literal))
	{
	case CHAR:
		print_char_literal(literal);
		break;
	case INT:
		print_int_literal(literal);
		break;
	case FLOAT:
		print_float_literal(literal);
		break;
	case DOUBLE:	
		print_double_literal(literal);
		break;
	case PSEUDO_D:
		print_pseudo_double_literal(literal);
		break;
	case PSEUDO_F:
		print_pseudo_float_literal(literal);
		break;
	case UNKNOWN:
		std::cout << "Error: unknown type\n";
		break;
	default:
	std::cout << "Error: no type found\n";
		break;
	}
}
