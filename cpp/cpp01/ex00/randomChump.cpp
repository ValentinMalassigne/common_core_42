#include "Zombie.hpp"
#include <iostream>

void randomChump(std::string name)
{
	Zombie zombie(name);
	zombie.announce();
}