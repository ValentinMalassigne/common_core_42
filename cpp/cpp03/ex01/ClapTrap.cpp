#include "ClapTrap.hpp"

//Constructors

ClapTrap::ClapTrap()
{
	std::cout << "ClapTrap default constructor called\n";
}

ClapTrap::ClapTrap(std::string c_name) : name(c_name), hit_points(10), eneregy_points(10), attack_damage(0)
{
	std::cout << "ClapTrap constructor with name called\n";
}

ClapTrap::ClapTrap(const ClapTrap &c_clapTrap)
{
	std::cout << "ClapTrap copy constructor called\n";
	*this = c_clapTrap;
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap destructor called\n";
}

//Overloads

ClapTrap& ClapTrap::operator=(const ClapTrap &other)
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

//Members

void ClapTrap::attack(const std::string& target)
{
	if (hit_points <= 0)
	{
		std::cout << "ClapTrap " << name << " is dead. It can't attack ...\n";
		return;
	}
	if (eneregy_points <= 0)
	{
		std::cout << "ClapTrap " << name << " don't have enough energy to attack.\n";
		return;
	}
	std::cout << "ClapTrap " << name << " attacks " << target << ", causing " << attack_damage << " points of damage!\n";
	eneregy_points--;
}

void ClapTrap::takeDamage(unsigned int amount)
{
	if (hit_points <= 0)
	{
		std::cout << "ClapTrap " << name << " is already dead ...\n";
		return;
	}
	std::cout << "ClapTrap " << name << " takes " << amount << " points of damages!\n";
	if (amount >= hit_points)
		hit_points = 0;
	else
		hit_points -= amount;
	std::cout << "ClapTrap " << name << " now have " << hit_points << " hit points.\n";
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (hit_points <= 0)
	{
		std::cout << "ClapTrap " << name << " is dead.\nIt can't be repaired ...\n";
		return;
	}
	if (eneregy_points <= 0)
	{
		std::cout << "ClapTrap " << name << " don't have enough energy to be repaire.\n";
		return;
	}
	hit_points += amount;
	std::cout << "ClapTrap " << name << " is repaired and now have " << hit_points << " hit points.\n";
}