#include "../headers/Dog.hpp"

Dog::Dog() : Animal("Dog")
{
	std::cout << "Dog default constructor called\n";
}

Dog::Dog(const Dog& other) : Animal()
{
	std::cout << "Dog copy constructor called\n";
	*this = other;
}

Dog::~Dog()
{
	std::cout << "Dog destructor called\n";
}

void Dog::makeSound(void) const
{
	std::cout << "WOUAF WOUAF WOUAF\n";
}

Dog& Dog::operator=(const Dog& other)
{
	if(this != &other)
	{
		this->type = other.type;
	}
	return *this;
}