#include "../headers/Brain.hpp"

Brain::Brain()
{
	std::cout << "Brain default constructor called\n";
}

Brain::Brain(const Brain &other)
{
	std::cout << "Brain copy constructor called\n";
	*this = other;
}

Brain::~Brain()
{
	std::cout << "Brain destructor called\n";
}

Brain& Brain::operator=(const Brain &other)
{
	for(int i = 0; i < BRAIN_CELLS; i++)
		ideas[i] = other.ideas[i];
	return(*this);
}

std::string Brain::readIdea(int index) const
{
	return ideas[index];
}

void Brain::saveIdea(int index, const std::string newIdea)
{
	ideas[index] = newIdea;
}