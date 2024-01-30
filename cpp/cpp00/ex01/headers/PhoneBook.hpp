#pragma once

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"

# define BOOK_SIZE 8

class PhoneBook {
public:
	PhoneBook() {
		last_contact_index = -1;
		for(int i = 0; i < BOOK_SIZE; i++)
			contacts[i].phone_number = -1;
	}

	void save_contact(Contact new_contact);

	int display_contacts();

	void display_contact(int index);

	bool check_index(int index);

private:
	Contact contacts[BOOK_SIZE];
	int	last_contact_index;

	void display_resized_string(std::string output);

	void display_first_line();

	void display_contact_line(int index);
};

#endif