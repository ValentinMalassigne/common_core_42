#pragma once

#include <iostream>
#include "Weapon.hpp"

class HumanA {
public:
	void attack();
	HumanA(std::string c_name, Weapon& c_weapon);
private:
	std::string name;
	Weapon* weapon;
};