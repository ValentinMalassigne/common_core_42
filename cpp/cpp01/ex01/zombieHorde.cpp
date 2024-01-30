#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string name)
{
	Zombie* zombieArray;

	zombieArray = new Zombie[N];
	for(int i = 0;i < N; i++)
		zombieArray[i].setName(name);
	return zombieArray;
}