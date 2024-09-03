#pragma once

#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>

class BitcoinExchange
{
public:
	BitcoinExchange();
	~BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &other);

	BitcoinExchange &operator=(const BitcoinExchange &other);

	void savePriceHistory(std::ifstream &price_history);

	void printValueForQuantityAtDate(const std::string &line) const;

private:
	std::map<std::string, float> priceHistory;

	std::pair<std::string, float> parse_input_line(std::string const &line) const;
	bool isDateInCorrectFormat(const std::string &date);
	bool isRateInCorrectFormat(const std::string &rate);
};