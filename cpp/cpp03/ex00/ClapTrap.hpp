#pragma once

#include <iostream>

class ClapTrap {
public:
	ClapTrap();
	ClapTrap(const std::string c_name);
	ClapTrap(const ClapTrap& c_clapTrap);
	~ClapTrap();

	ClapTrap &operator=(const ClapTrap &other);

	void attack(const std::string& target);
	void takeDamage(unsigned int amount);
	void beRepaired(unsigned int amount);

private:
	std::string name;
	unsigned int hit_points;
	unsigned int eneregy_points;
	unsigned int attack_damage;
};