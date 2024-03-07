#include <iostream>

int main()
{
	std::string hi_string = "HI THIS IS BRAIN";
	std::string* stringPTR = &hi_string;
	std::string& stringREF = hi_string;

	std::cout << "address of hi_string : " << &hi_string << std::endl;
	std::cout << "address held by stringPTR : " << stringPTR << std::endl;
	std::cout << "address held by ref_to_str : " << &stringREF << std::endl;

	std::cout << "value of hi_string : " << hi_string << std::endl;
	std::cout << "value of pointed by stringPTR : " << *stringPTR << std::endl;
	std::cout << "value of ref_to_str : " << stringREF << std::endl;

	return (0);
}