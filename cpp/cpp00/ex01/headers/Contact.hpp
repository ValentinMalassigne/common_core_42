#ifndef CONTACT_HPP
# define CONTACT_HPP

class Contact {
public:
	std::string first_name;
	std::string last_name;
	std::string nickname;
	std::string darkest_secret;
	int phone_number;

	void add_contact();

private:
	std::string get_string_input(std::string prompt);
	int get_int_input(std::string prompt);
	bool is_string_input_valid(std::string input);
	bool is_int_input_valid(std::string input);
	int stoi(std::string str);
};

#endif