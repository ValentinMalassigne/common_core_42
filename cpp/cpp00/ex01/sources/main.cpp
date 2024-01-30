#include <iostream>
#include <sstream>
#include "../headers/Contact.hpp"
#include "../headers/PhoneBook.hpp"

void welcome_message() {
	std::cout << "\n	--------------------\n" << "	My Awesome PhoneBook\n" << "	--------------------\n\n";
	std::cout << "Possible actions : \n";
	std::cout << "ADD\tType ADD to add a contact to your PhoneBook\n";
	std::cout << "SEARCH\tType SEARCH to search in your PhoneBook\n";
	std::cout << "EXIT\tType EXIT to exit your PhoneBook safely\n";	
}

void manage_add_contact(PhoneBook *phoneBook)
{
	Contact new_contact;

	new_contact.create_new_contact();
	(*phoneBook).save_contact(new_contact);
	std::cout << "\nSuccessfully added the new contact\n";
}

int custom_stoi(std::string str)
{
	int result;
	std::istringstream iss(str);
		iss >> result;
	return (result);
}

bool selected_index_is_valid(std::string input, PhoneBook phoneBook)
{
	int check_number;

	for (size_t i = 0; i < input.length(); i++) {
        if (!std::isdigit(input[i])) {
			std::cout << "Invalid input : input must be numeric\n";
            return false;
        }
    }
	try {
		check_number = custom_stoi(input);
	} catch (std::invalid_argument&) {
		std::cout << "Invalid input : invalid arguments\n";
		return (false);
	} catch (std::out_of_range&) {
		std::cout << "Invalid input : value out of range\n";
		return (false);
	}
	if (check_number < 0 || check_number >= BOOK_SIZE)
	{
		std::cout << "Invalid input : value must be between 0 and 7\n";
		return (false);
	}
	if(!phoneBook.check_index(check_number))
	{
		std::cout << "Invalid input : This index is not available\n";
		return (false);
	}
	return (true);
}

void manage_search(PhoneBook phoneBook)
{
	int displayed_count;
	Contact selectedContact;
	std::string input = "";

	displayed_count = phoneBook.display_contacts();
	if (!displayed_count)
		return;
	std::cout << std::endl << "Type an index to get this contact informations\n";
	while (true)
	{
		std::getline(std::cin, input);
		if (selected_index_is_valid(input, phoneBook))
			break;
	}
	phoneBook.display_contact(custom_stoi(input));
}

void input_loop() {
	PhoneBook phoneBook = PhoneBook();
	std::string input = "";

	while (input != "EXIT")
	{
		std::getline(std::cin, input);
		if (input == "ADD")
			manage_add_contact(&phoneBook);
		if (input == "SEARCH")
			manage_search(phoneBook);
	}
}

int main()
{
	welcome_message();
	input_loop();
	return (0);
}