#pragma once

#include "Animal.hpp"
#include "iostream"

class Cat : public Animal {
public:
	Cat();
	Cat(const Cat& c_cat);
	~Cat();

	Cat& operator=(const Cat& other);
	void makeSound() const;
};