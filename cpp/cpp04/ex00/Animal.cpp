#include "Animal.hpp"

Animal::Animal()
{
	std::cout << "Animal default constructor called\n";
}

Animal::Animal(const Animal& other)
{
	std::cout << "Animal copy constructor called\n";	
	*this = other;
}

Animal::~Animal()
{
	std::cout << "Animal destructor called\n";
}

Animal& Animal::operator=(const Animal& other)
{
	if (this != &other)
		type = other.type;
	return *this;
}

void Animal::makeSound() const
{
	if (type == "Dog")
		std::cout << "WOUAF WOUAF WOUAF\n";
	else if (type == "Cat")
		std::cout << "miaou miaou\n";
}

std::string Animal::getType() const
{
	return type;
}