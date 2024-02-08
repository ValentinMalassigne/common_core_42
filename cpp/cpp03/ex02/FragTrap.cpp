#include "FragTrap.hpp"

FragTrap::FragTrap()
{
	std::cout << "FragTrap default constructor called\n";
	this->hit_points = 100;
	this->eneregy_points = 100;
	this->attack_damage = 30;
}

FragTrap::FragTrap(const std::string& c_name) : ClapTrap(c_name)
{
	std::cout << "FragTrap constructor with name called\n";
	this->hit_points = 100;
	this->eneregy_points = 100;
	this->attack_damage = 30;
}

FragTrap::FragTrap(const FragTrap& c_fragTrap)
{
	std::cout << "ClapTrap copy constructor called\n";
	*this = c_fragTrap;
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap destructor called\n";

}

FragTrap& FragTrap::operator=(const FragTrap& other)
{
	if (this != &other)
	{
		this->attack_damage = other.attack_damage;
		this->eneregy_points = other.eneregy_points;
		this->hit_points = other.hit_points;
		this->name = other.name;
	}
	return *this;
}

void FragTrap::highFivesGuys()
{
	std::cout << "FragTrap " << name << " request a positive high fives\n";
}