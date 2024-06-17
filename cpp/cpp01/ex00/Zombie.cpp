#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie(std::string c_name)
{
	name = c_name;
}

Zombie::~Zombie()
{
	std::cout << name <<": destroyed\n";
}

void Zombie::announce(void)
{
	std::cout << name << ": BraiiiiiiinnnzzzZ...\n";
}