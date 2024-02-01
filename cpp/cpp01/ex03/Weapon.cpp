#include "Weapon.hpp"

Weapon::Weapon(std::string c_type)
{
	type = c_type;
}

const std::string& Weapon::getType()
{
	return (type);
}

void Weapon::setType(std::string new_type)
{
	type = new_type;
}