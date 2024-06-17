#include "../headers/WrongCat.hpp"

WrongCat::WrongCat() : WrongAnimal("WrongCat")
{
	std::cout << "Cat default constructor called\n";
}

WrongCat::WrongCat(const WrongCat& other) : WrongAnimal()
{
	std::cout << "WrongCat copy constructor called\n";
	*this = other;
}

WrongCat::~WrongCat()
{
	std::cout << "WrongCat destructor called\n";
}

void WrongCat::makeSound() const
{
	std::cout << "Wrong miaou miaou\n";
}


WrongCat& WrongCat::operator=(const WrongCat& other)
{
	if (this != &other)
	{
		this->type = other.type;
	}
	return *this;
}