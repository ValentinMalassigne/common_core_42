#pragma once

#include <iostream>

class Animal {
public:
	Animal( void );
	Animal(const Animal& c_animal);
	~Animal();

	Animal& operator=(const Animal& other);

	void makeSound() const;
	std::string getType() const;


protected: 
	std::string type;

};