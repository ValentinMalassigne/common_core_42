#include "../headers/Data.hpp"

Data::Data()
{}

Data::Data(const int c_age, const std::string c_name) : age(c_age), name(c_name)
{}

Data::Data(const Data &other)
{
	*this = other;
}

Data::~Data()
{}

Data& Data::operator=(const Data &other)
{
	if (this == &other)
		return *this;
	age = other.age;
	name = other.name;
	return *this;
}