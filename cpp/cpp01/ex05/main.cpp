#include "iostream"
#include "Harl.hpp"

int main()
{
	Harl harl;
	std::string input = "";
	while (true)
	{
		std::getline(std::cin, input);
		if (input == "debug" || input == "info" ||input == "warning" ||input == "error")
			harl.complain(input);
		if (input == "exit")
			break;
	}
	return (0);
}
