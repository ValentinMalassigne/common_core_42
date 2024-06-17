#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <limits>

class ScalarConverter
{
private:
	ScalarConverter(); // private constructor to prevent instantiation
	ScalarConverter(const ScalarConverter &other);
	~ScalarConverter();

	ScalarConverter& operator=(const ScalarConverter& other);

public:
	static void convert(const std::string &literal);
};

/*
https://www.learncpp.com/cpp-tutorial/static-member-functions/
https://en.cppreference.com/w/cpp/language/string_literal
Because static member functions are not associated with a particular object,
they can be called directly by using the class name and the scope resolution operator
(e.g. Something::getValue()).
Like static member variables, they can also be called through objects of the class type,
though this is not recommended.
Static member functions are not attached to an object so they have no "this" pointer!
Static member functions can directly access other static members (variables or functions),
but not non-static members.
*/

/*
static_cast: This is a type of explicit casting where you explicitly tell the compiler to convert one type to another.
It is mainly used for conversions that are well-defined and safe at compile-time.
int i = 10;
double d = static_cast<double>(i); // Converting integer i to double

Implicit Casts: These are automatic conversions performed by the compiler when it is safe to do so.
int i = 10;
long l = i; // Implicit conversion from int to long

Promotion Casts: This refers to the automatic conversion of data types to wider types in expressions.
int i = 10;
float f = 5.5;
float result = i + f; // i is promoted to float before addition
*/