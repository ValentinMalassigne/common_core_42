#include <iostream>
#include "../headers/Contact.hpp"

void welcome_message() {
	std::cout << "\n	--------------------\n" << "	My Awesome PhoneBook\n" << "	--------------------\n\n";
	std::cout << "Possible actions : \n";
	std::cout << "ADD\tType ADD to add a contact to your PhoneBook\n";
	std::cout << "SEARCH\tType SEARCH to search in your PhoneBook\n";
	std::cout << "EXIT\tType EXIT to exit your PhoneBook safely\n";	
}

void manage_add_contact()
{
	Contact new_contact;
	new_contact.add_contact();
}

void input_loop() {
	std::string input = "";

	while (input != "EXIT")
	{
		std::getline(std::cin, input);
		if (input == "ADD")
			manage_add_contact();
	}
}

int main()
{
	welcome_message();
	input_loop();
	return (0);
}