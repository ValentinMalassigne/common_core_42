#include "HumanA.hpp"

HumanA::HumanA(std::string c_name, Weapon& c_weapon) : name(c_name), weapon(&c_weapon)
{}

void HumanA::attack()
{
	std::cout << name << " attacks with their " << weapon->getType() << std::endl;
}
