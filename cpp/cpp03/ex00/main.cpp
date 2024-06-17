#include "ClapTrap.hpp"

int main()
{
	ClapTrap clapTrap1 = ClapTrap("clapTrap1");

	clapTrap1.attack("Bad Guy");

	clapTrap1.takeDamage(5);

	clapTrap1.beRepaired(3);

	clapTrap1.takeDamage(10);

	clapTrap1.attack("Bad Guy");
}