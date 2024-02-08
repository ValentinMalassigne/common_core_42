#include "Dog.hpp"

Dog::Dog()
{
	this->type = "Dog";
	std::cout << "Dog default constructor called\n";
}

Dog::Dog(const Dog& other)
{
	std::cout << "Dog copy constructor called\n";
	*this = other;
}

Dog::~Dog()
{
	std::cout << "Dog destructor called\n";
}

Dog& Dog::operator=(const Dog& other)
{
	if(this != &other)
	{
		this->type = other.type;
	}
	return *this;
}