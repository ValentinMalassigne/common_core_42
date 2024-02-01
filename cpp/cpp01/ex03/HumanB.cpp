#include "HumanB.hpp"

HumanB::HumanB(std::string c_name) : name(c_name)
{}

void HumanB::setWeapon(Weapon& new_weapon)
{
	weapon = &new_weapon;
}

void HumanB::attack()
{
	std::cout << name << " attacks with their " << weapon->getType() << std::endl;
}