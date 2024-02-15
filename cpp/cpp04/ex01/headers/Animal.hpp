#pragma once

#include <iostream>
#include "Brain.hpp"

class Animal {
public:
	Animal( void );
	Animal(const Animal& c_animal);
	Animal(const std::string type);
	virtual ~Animal();

	Animal& operator=(const Animal& other);

	virtual void makeSound() const;
	std::string getType() const;

protected: 
	std::string type;
};
