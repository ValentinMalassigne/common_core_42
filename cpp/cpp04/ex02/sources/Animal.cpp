#include "../headers/Animal.hpp"

Animal::Animal()
{
	std::cout << "Animal default constructor called\n";
}

Animal::Animal(const Animal& other)
{
	std::cout << "Animal copy constructor called\n";	
	*this = other;
}

Animal::Animal(const std::string c_type) : type(c_type)
{
	std::cout << "Animal type constructor called\n";
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
	std::cout << "Animal sound\n";	
}

std::string Animal::getType() const
{
	return type;
}