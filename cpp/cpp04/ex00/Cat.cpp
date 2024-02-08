#include "Cat.hpp"

Cat::Cat()
{
	this->type = "Cat";
	std::cout << "Cat default constructor called\n";
}

Cat::Cat(const Cat& other)
{
	std::cout << "Cat copy constructor called\n";
	*this = other;
}

Cat::~Cat()
{
	std::cout << "Cat destructor called\n";
}

Cat& Cat::operator=(const Cat& other)
{
	if (this != &other)
	{
		this->type = other.type;
	}
	return *this;
}