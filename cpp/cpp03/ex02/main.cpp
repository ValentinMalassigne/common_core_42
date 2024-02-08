#include "FragTrap.hpp"

int main()
{
	FragTrap fragTrap1 = FragTrap("fragTrap1");

	fragTrap1.attack("Bad Guy");

	fragTrap1.takeDamage(5);

	fragTrap1.beRepaired(3);

	fragTrap1.highFivesGuys();
}