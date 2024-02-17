#include "../headers/Dog.hpp"

Dog::Dog() : Animal("Dog")
{
	brain = new Brain();
	std::cout << "Dog default constructor called\n";
}

Dog::Dog(const Dog& other) : Animal(other.type)
{
	brain = new Brain();
	std::cout << "Dog copy constructor called\n";
	*this = other;
}

Dog::~Dog()
{
	delete brain;
	std::cout << "Dog destructor called\n";
}

void Dog::makeSound(void) const
{
	std::cout << "WOUAF WOUAF WOUAF\n";
}

Dog& Dog::operator=(const Dog& other)
{
	if (this != &other)
	{
		this->type = other.type;
		if (brain != NULL)
			delete (brain);
		brain = new Brain(*other.brain);
	}
	return *this;
}

Brain* Dog::getBrain() const
{
	return brain;
}