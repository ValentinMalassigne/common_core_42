#include "../headers/ScalarConverter.hpp"

int main()
{
	ScalarConverter::convert("'c'");
	ScalarConverter::convert("'a'");
	ScalarConverter::convert("0");
	ScalarConverter::convert("-42");
	ScalarConverter::convert("42");
	ScalarConverter::convert("0.0f");
	ScalarConverter::convert("-4.2f");
	ScalarConverter::convert("4.2f");
	ScalarConverter::convert("-inff");
	ScalarConverter::convert("+inff");
	ScalarConverter::convert("0.0");
	ScalarConverter::convert("-4.2");
	ScalarConverter::convert("4.2");
	ScalarConverter::convert("-inf");
	ScalarConverter::convert("+inf");
	ScalarConverter::convert("nan");

	return 0;
}