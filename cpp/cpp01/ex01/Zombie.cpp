#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie()
{
	std::cout << "zombie created\n";
}

Zombie::~Zombie()
{
	std::cout << name <<": destroyed\n";
}

void Zombie::announce(void)
{
	std::cout << name << ": BraiiiiiiinnnzzzZ...\n";
}

void Zombie::setName(std::string new_name)
{
	name = new_name;
}