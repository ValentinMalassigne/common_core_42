#include "Zombie.hpp"

int main()
{
	int zombieCount = 10;
	Zombie* zombieArray = zombieHorde(zombieCount, "Etienne");
	for(int i = 0; i < zombieCount;i++)
	{
		zombieArray[i].announce();
	}
	delete[] zombieArray;
	return (0);
}