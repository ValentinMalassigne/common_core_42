#pragma once

#include <string>

class Weapon {
public:
	Weapon(std::string c_type);

	const std::string& getType();

	void setType(std::string new_type);

private:
	std::string type;
};
