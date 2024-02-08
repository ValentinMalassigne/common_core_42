#include "ScavTrap.hpp"

int main()
{
	ScavTrap scavTrap1 = ScavTrap("scavTrap1");

	scavTrap1.attack("Bad Guy");

	scavTrap1.takeDamage(5);

	scavTrap1.beRepaired(3);

	scavTrap1.guardGate();
}