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

	virtual void makeSound() const = 0;
	std::string getType() const;

protected: 
	std::string type;
};
/*

virtual void makeSound() = 0;
This is called a pure virtual function.
virtual keyword allows for dynamic binding of the function at runtime
when using the function on a child class

An abstract class is a class that contains at least one pure virtual function

It is not possible to create an instance of an abstract class
But it is possible to create pointers and references to an abstract class

If a child class does not implement the pure virtual functions of it's parent
The child class will also become an abstract class
*/