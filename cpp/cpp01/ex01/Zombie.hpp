#pragma once

#include <string>

class Zombie {
public:
	Zombie();
	~Zombie();
	
	void announce(void);

	void setName(std::string new_name);

private:
	std::string name;
};

Zombie* zombieHorde(int N, std::string name);