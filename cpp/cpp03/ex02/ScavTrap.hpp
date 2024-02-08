#pragma once

#include "ClapTrap.hpp"
#include <iostream>

class ScavTrap : public ClapTrap {
public:
	ScavTrap();
	ScavTrap(const std::string& c_name);
	ScavTrap(const ScavTrap& c_scavTrap);
	~ScavTrap();

	ScavTrap& operator=(const ScavTrap& other);

	void guardGate();
	void attack(const std::string& target);
}; 