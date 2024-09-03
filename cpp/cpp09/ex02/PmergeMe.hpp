#include <string>
#include <iostream>

#include <list>
#include <vector>
#include <ctime>
#include <iostream>
#include <limits>
#include <sstream>

class PmergeMe
{
public:
	PmergeMe();
	PmergeMe(const PmergeMe &other);
	~PmergeMe();

	PmergeMe &operator=(const PmergeMe &other);

	static void sort(std::string input);
	static bool verify_input(std::string input);
};