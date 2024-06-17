#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "BitcoinExchange.hpp"

int display_exit_error(std::string const &error_message)
{
	std::cout << "Error : " << error_message << std::endl;
	return 1;
}

int main(int argc, char **argv)
{
	std::ifstream inputFile;
	std::ifstream price_history;

	if (argc != 2)
		return display_exit_error("Invalid number of arguments");
	inputFile.open(argv[1]);
	if (!inputFile.is_open())
		return display_exit_error("Error while trying to open " + std::string(argv[1]));

	price_history.open("data.csv");
	if (!price_history.is_open())
	{
		inputFile.close();
		return display_exit_error("Error while trying to open data.csv");
	}

	BitcoinExchange btc;
	btc.savePriceHistory(price_history);
	price_history.close();

	std::string current_line;
	std::getline(inputFile, current_line);
	while (std::getline(inputFile, current_line))
	{
		try
		{
			btc.printValueForQuantityAtDate(current_line);
		}
		catch (std::exception &e)
		{
			std::cout << e.what();
			continue;
		}
	}

	inputFile.close();
	return 0;
}