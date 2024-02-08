#pragma once

#include "ClapTrap.hpp"
#include <iostream>

class FragTrap : public ClapTrap {
public:
	FragTrap();
	FragTrap(const std::string& c_name);
	FragTrap(const FragTrap& c_fragTrap);
	~FragTrap();

	FragTrap &operator=(const FragTrap& other);

	void highFivesGuys(void);
};