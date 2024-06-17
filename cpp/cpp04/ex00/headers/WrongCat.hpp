#pragma once

#include "WrongAnimal.hpp"
#include "iostream"

class WrongCat : public WrongAnimal {
public:
	WrongCat();
	WrongCat(const WrongCat& c_cat);
	~WrongCat();

	WrongCat& operator=(const WrongCat& other);
	void makeSound() const;
};