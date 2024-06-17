#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	*this = other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
	{
		this->priceHistory = other.priceHistory;
	}
	return *this;
}

// Utils

bool BitcoinExchange::isDateInCorrectFormat(const std::string &date)
{
	if (date.length() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;
	for (size_t i = 0; i < date.length(); i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(date[i]))
			return false;
	}
	return true;
}

bool BitcoinExchange::isRateInCorrectFormat(const std::string &rate)
{
	int minus_count = 0;
	if (rate.empty())
		return false;
	for (size_t i = 0; i < rate.length(); i++)
	{
		if (!std::isdigit(rate[i]) && rate[i] != '.' && rate[i] != '-')
			return false;
		if (rate[i] == '-')
			minus_count++;
	}
	if (minus_count > 1)
	{
		return false;
	}
	try
	{
		std::stof(rate);
	}
	catch (const std::out_of_range &oor)
	{
		return false;
	}
	catch (const std::exception &e)
	{
		std::cout << "Error : Exception : " << e.what() << "on\"" << rate << "\"\n";
		return false;
	}
	return true;
}

// Price history

void BitcoinExchange::savePriceHistory(std::ifstream &price_history)
{
	std::string current_line;
	size_t delim;

	std::getline(price_history, current_line);
	while (std::getline(price_history, current_line))
	{
		try
		{
			delim = current_line.find(',');
			if (delim == std::string::npos)
			{
				std::cout << "CSV Error : Bad input : \"" << current_line << "\"\n";
				continue;
			}
			std::string date = current_line.substr(0, delim);
			std::string rate_as_str = current_line.substr(delim + 1);
			if (isDateInCorrectFormat(date) && isRateInCorrectFormat(rate_as_str))
			{
				float rate = std::stof(rate_as_str);
				priceHistory[date] = rate;
			}
		}
		catch (const std::exception &e)
		{
			std::cerr << "Save History Error : Exception : " << e.what() << "on\"" << current_line << "\"\n";
		}
	}
}

// Input

std::pair<std::string, float> BitcoinExchange::parse_input_line(std::string const &line) const
{
	BitcoinExchange btc;

	size_t delim = line.find('|');
	if (delim == std::string::npos)
		throw std::runtime_error("Error : Bad input => " + line + "\n");

	std::string date = line.substr(0, delim - 1);
	if (!btc.isDateInCorrectFormat(date))
		throw std::runtime_error("Error : Bad date format =>" + line + "\n");

	std::string quantity_as_str = line.substr(delim + 2);
	if (!btc.isRateInCorrectFormat(quantity_as_str))
		throw std::runtime_error("Error : Bad value format =>" + line + "\n");

	float quantity = std::stof(quantity_as_str);
	if (quantity < 0)
		throw std::runtime_error("Error : not a positive number.\n");
	if (quantity > 1000)
		throw std::runtime_error("Error : too large number.\n");
	std::pair<std::string, float> result;
	result.first = date;
	result.second = quantity;
	return result;
}

void BitcoinExchange::printValueForQuantityAtDate(const std::string &line) const
{
	std::pair<std::string, float> input = parse_input_line(line);
	std::string date = input.first;
	float quantity = input.second;

	std::map<std::string, float>::const_iterator iter = priceHistory.lower_bound(date);
	if (iter != priceHistory.begin())
	{
		if (iter == priceHistory.end() || iter->first != date)
		{
			--iter;
		}
	}
	else
	{
		if (date < iter->first)
			throw std::runtime_error(date + " => No available date in price history\n");
	}

	if (iter == priceHistory.end())
	{
		throw std::runtime_error(date + " => No available date in price history\n");
	}

	float price = iter->second;

	float value = price * quantity;
	std::cout << date << " => " << quantity << " = " << value << std::endl;
}
