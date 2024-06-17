#include <iostream>
#include "PmergeMe.hpp"

std::string parsed_input(char **input)
{
	std::string parsed_input = "";
	for (int i = 1; input[i]; i++)
	{
		parsed_input += input[i];
		if (input[i + 1])
			parsed_input += " ";
	}
	return parsed_input;
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "Usage: ./ex02 \"positive numbers list\"" << std::endl;
		return 1;
	}

	std::string input = parsed_input(argv);

	PmergeMe p;
	p.sort(input);
	return 0;
}