#pragma once

#include "Animal.hpp"
#include "iostream"
#include "Brain.hpp"

class Cat : public Animal {
public:
	Cat();
	Cat(const Cat& c_cat);
	~Cat();

	Cat& operator=(const Cat& other);
	void makeSound() const;
	Brain *getBrain() const;

private:
	Brain *brain;
};