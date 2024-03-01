#include <iostream>
#include <string>
#include <sstream>
#include <limits>

class ScalarConverter
{
private:
	ScalarConverter(); // private constructor to prevent instantiation

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