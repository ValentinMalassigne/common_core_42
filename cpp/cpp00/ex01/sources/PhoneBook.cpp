#include "../headers/PhoneBook.hpp"

void PhoneBook::save_contact(Contact new_contact)
{
	last_contact_index = (last_contact_index + 1) % BOOK_SIZE;
	contacts[last_contact_index] = new_contact;
}

int PhoneBook::display_contacts()
{
	int displayed_count = 0;
	for(int i = 0; i < BOOK_SIZE; i++)
	{
		if (contacts[i].phone_number >= 0)
		{
			displayed_count++;
		}
	}
	if (!displayed_count)
	{
		std::cout << "\nYour contact book is empty. Add a contact first\n\n";
		return (displayed_count);
	}
	display_first_line();
	for(int i = 0; i < BOOK_SIZE; i++)
	{
		if (contacts[i].phone_number >= 0)
		{
			display_contact_line(i);
		}
	}
	return (displayed_count);
}

void PhoneBook::display_contact_line(int index)
{
	std::stringstream ss;

    ss << index;
	display_resized_string(ss.str());
	std::cout << '|';
	display_resized_string(contacts[index].first_name);
	std::cout << '|';
	display_resized_string(contacts[index].last_name);
	std::cout << '|';
	display_resized_string(contacts[index].nickname);
	std::cout << std::endl;
}

void PhoneBook::display_first_line()
{
	std::cout << std::endl;
	display_resized_string("index");
	std::cout << '|';
	display_resized_string("first name");
	std::cout << '|';
	display_resized_string("last name");
	std::cout << '|';
	display_resized_string("nickmame");
	std::cout << std::endl;
}

void PhoneBook::display_resized_string(std::string output)
{
	int i = 0;
	int j = 0;
	while ((i + output.length()) < 10)
	{
		std::cout << ' ';
		i++;
	}
	while (i + j < 10)
	{
		if (i + j == 9 && output.length() > 10)
		{
			std::cout << '.';
			break;
		}
		std::cout << output[j];
		j++;
	}
}

bool PhoneBook::check_index(int index)
{
	if (contacts[index].phone_number >= 0)
		return (true);
	return (false);
}

void PhoneBook::display_contact(int index)
{
	std::cout << std::endl;
	std::cout << "first name\t: " << contacts[index].first_name << std::endl;
	std::cout << "last name \t: " << contacts[index].last_name << std::endl;
	std::cout << "nickname \t: " << contacts[index].nickname << std::endl;
	std::cout << "darkest secret \t: " << contacts[index].darkest_secret << std::endl;
	std::cout << "phone number \t: " << contacts[index].phone_number << std::endl;
}