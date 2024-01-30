#pragma once

#include <string>

class Zombie {
public:
	Zombie(std::string c_name);
	~Zombie();
	void announce(void);

private:
	std::string name;
};

void randomChump(std::string name);
Zombie* newZombie(std::string name);