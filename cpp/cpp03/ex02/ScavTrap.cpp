#include "ScavTrap.hpp"

ScavTrap::ScavTrap()
{
	std::cout << "ScavTrap default constructor called\n";
	this->hit_points = 100;
	this->eneregy_points = 50;
	this->attack_damage = 20;
}

ScavTrap::ScavTrap(const std::string& c_name) : ClapTrap(c_name) 
{
	std::cout << "ScavTrap constructor with name called\n";
	this->hit_points = 100;
	this->eneregy_points = 50;
	this->attack_damage = 20;
}

ScavTrap::ScavTrap(const ScavTrap &c_scavTrap)
{
	std::cout << "ScavTrap copy constructor called\n";
	*this = c_scavTrap;
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap destructor called\n";
}

ScavTrap& ScavTrap::operator=(const ScavTrap& other)
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

void ScavTrap::attack(const std::string& target)
{
	if (hit_points <= 0)
	{
		std::cout << "ScavTrap " << name << " is dead. It can't attack ...\n";
		return;
	}
	if (eneregy_points <= 0)
	{
		std::cout << "ScavTrap " << name << " don't have enough energy to attack.\n";
		return;
	}
	std::cout << "ScavTrap " << name << " attacks " << target << ", causing " << attack_damage << " points of damage!\n";
	eneregy_points--;
}

void ScavTrap::guardGate()
{
	std::cout << "ScavTrap " << name << "is now in Gate keeper mode.\n";
}