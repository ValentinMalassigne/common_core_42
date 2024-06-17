#include "Zombie.hpp"

int main()
{
	randomChump("InTheStack");
	Zombie* zombie = newZombie("InTheHeap");
	if (zombie)
		zombie->announce();
	delete zombie;
	return 0;
}