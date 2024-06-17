#include "../headers/utils.hpp"

bool checkCharType(const std::string &literal)
{
	if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'')
		return true;
	return false;
}

bool checkIntType(const std::string &literal)
{
	int pos = 0;
	if (literal[0] == '+' || literal[0] == '-')
		pos++;
	if(literal.find_first_not_of("0123456789", pos) != std::string::npos)
		return false;
	return true;
}

bool checkFloatType(const std::string &literal)
{
	int pos = 0;
	if (literal[0] == '+' || literal[0] == '-')
		pos++;
	if(literal.find_first_not_of("0123456789.f", pos) != std::string::npos || literal.find_first_of(".") != literal.find_last_of(".") || literal.find_first_of("f") != literal.find_last_of("f") || literal[literal.length() - 1] != 'f')
		return false;
	return true;
}

bool checkDoubleType(const std::string &literal)
{
	int pos = 0;
	if (literal[0] == '+' || literal[0] == '-')
		pos++;
	if(literal.find_first_not_of("0123456789.", pos) != std::string::npos || literal.find_first_of(".") != literal.find_last_of("."))
		return false;
	return true;
}

bool checkPseudoDoubleType(const std::string &literal)
{
	if (literal == "nan" || literal == "+inf" || literal == "-inf" || literal == "inf")
		return true;
	return false;
}

bool checkPseudoFloatType(const std::string &literal)
{
	if (literal == "+inff" || literal == "-inff" || literal == "inff")
		return true;
	return false;
}

t_literal_type getType(const std::string &literal)
{
	if (checkCharType(literal))
		return CHAR;
	else if (checkIntType(literal))
		return INT;
	else if (checkFloatType(literal))
		return FLOAT;
	else if (checkDoubleType(literal))
		return DOUBLE;
	else if (checkPseudoDoubleType(literal))
		return PSEUDO_D;
	else if (checkPseudoFloatType(literal))
		return PSEUDO_F;
	return UNKNOWN;
}
