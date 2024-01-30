#include "../headers/Contact.hpp"

void Contact::create_new_contact()
{
	std::cout << std::endl;
	first_name = get_string_input("first name : ");
	last_name = get_string_input("last name : ");
	nickname = get_string_input("nickname : ");
	darkest_secret = get_string_input("darkest secret : ");
	phone_number = get_int_input("phone number : ");
}

std::string Contact::get_string_input(std::string prompt)
{
	std::string input = "";
	while (true)
	{
		std::cout << prompt;
		std::getline(std::cin, input);
		if (is_string_input_valid(input))
			return (input);
		std::cout << "Invalid input, input must not be empty\n";
	}
}

int Contact::get_int_input(std::string prompt)
{
	std::string input = "";
	while (true)
	{
		std::cout << prompt;
		std::getline(std::cin, input);
		if (is_int_input_valid(input))
			return (stoi(input));
		std::cout << "Invalid input, input must be a positive integer\n";
	}
}

bool Contact::is_string_input_valid(std::string input)
{
	if (input.empty())
		return (false);
	return (true);
}

bool Contact::is_int_input_valid(std::string input)
{
	int check_number;
	if (input.empty())
		return (false);
	if (!std::isdigit(input[0]) && input[0] != '+')
		return (false);
	for (size_t i = 1; i < input.length();i ++) {
        if (!std::isdigit(input[i])) {
            return false;
        }
    }
	try {
		check_number = stoi(input);
	} catch (std::invalid_argument&) {
		return (false);
	} catch (std::out_of_range&) {
		return (false);
	}
	if (check_number < 0)
		return (false);
	return (true);
}

int Contact::stoi(std::string str)
{
	int result;
	std::istringstream iss(str);
		iss >> result;
	return (result);
}
