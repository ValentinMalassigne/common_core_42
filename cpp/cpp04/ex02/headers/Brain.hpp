#pragma once

#include <iostream>

class Brain
{
public:
	Brain();
	Brain(const Brain &c_brain);
	~Brain();

	Brain& operator=(const Brain &other);

	std::string readIdea(int index) const;
	void saveIdea(int index, const std::string newIdea);
	

private:
	static const int BRAIN_CELLS = 100;
	std::string ideas[BRAIN_CELLS];
};