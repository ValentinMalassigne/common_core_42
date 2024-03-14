#pragma once

#include <string>
#include "ScalarConverter.hpp"

typedef enum e_literal_type
	{
		CHAR,
		INT,
		FLOAT,
		DOUBLE,
		PSEUDO_D,
		PSEUDO_F,
		UNKNOWN,
	} t_literal_type;

t_literal_type getType(const std::string &literal);
void print_char_literal(const std::string &literal);
void print_int_literal(const std::string &literal);
void print_float_literal(const std::string &literal);
void print_double_literal(const std::string &literal);
void print_pseudo_float_literal(const std::string &literal);
void print_pseudo_double_literal(const std::string &literal);