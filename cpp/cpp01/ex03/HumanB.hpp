#pragma once

#include <iostream>
#include "Weapon.hpp"

class HumanB {
public:
	HumanB(std::string c_name);

	void setWeapon(Weapon& new_weapon);

	void attack();

private:
	std::string name;
	Weapon* weapon;
};