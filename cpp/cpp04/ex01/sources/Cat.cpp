#include "../headers/Cat.hpp"

Cat::Cat() : Animal("Cat")
{
	brain = new Brain();
	std::cout << "Cat default constructor called\n";
}

Cat::Cat(const Cat& other) : Animal(other.type)
{
	std::cout << "Cat copy constructor called\n";
	*this = other;
}

Cat::~Cat()
{
	delete brain;
	std::cout << "Cat destructor called\n";
}

void Cat::makeSound() const
{
	std::cout << "miaou miaou\n";
}


Cat& Cat::operator=(const Cat& other)
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

Brain* Cat::getBrain() const
{
	return brain;
}