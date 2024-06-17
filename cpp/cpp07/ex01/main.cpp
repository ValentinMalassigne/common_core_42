#include "iter.hpp"

int main() {
	int intArray[] = {1, 2, 3, 4, 5};
	::iter(intArray, 5, print);
	std::cout << std::endl;

	std::string stringArray[] = {"one", "two", "three", "four", "five"};
	::iter(stringArray, 5, print);
	std::cout << std::endl;

	return 0;
}

