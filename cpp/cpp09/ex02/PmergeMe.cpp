#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){};

PmergeMe::PmergeMe(const PmergeMe &other)
{
	*this = other;
}

PmergeMe::~PmergeMe(){};

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	(void)other;
	return *this;
}

bool PmergeMe::verify_input(std::string input)
{
	if (input.empty())
	{
		std::cout << "Empty input" << std::endl;
		return false;
	}
	for (size_t i = 0; i < input.length(); i++)
	{
		if (!isdigit(input[i]) && input[i] != ' ')
		{
			if (input[i] == '-')
				std::cout << "Negative numbers are not allowed" << std::endl;
			else
				std::cout << "Invalid character : " << input[i] << std::endl;
			return false;
		}
		if ((i == 0 || i == input.length() - 1) && input[i] == ' ')
		{
			std::cout << "Invalid space position" << std::endl;
			return false;
		}
		else if (input[i] == ' ' && input[i + 1] == ' ')
		{
			std::cout << "Consecutive spaces" << std::endl;
			return false;
		}
	}
	return true;
}

int stoi(std::string str)
{
	std::stringstream ss(str);
	int i;
	ss >> i;

	if (i == std::numeric_limits<int>::max())
        std::runtime_error("int Overflow occurred!");
	return i;
}

template <typename T>
static void initialize_container(T &res, std::string input)
{
	std::string number = "";

	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] == ' ')
		{
			res.push_back(stoi(number));
			number = "";
		}
		else
			number += input[i];
	}
	res.push_back(stoi(number));
}

template <typename T>
static void print_container(T container, int limit)
{
	int i = 0;
	for (typename T::iterator it = container.begin(); it != container.end(); it++)
	{
		std::cout << *it;
		if (it != --container.end())
			std::cout << " ";
		i++;
		if (i > limit)
		{
			std::cout << " [...]";
			break;
		}
	}
	std::cout << std::endl;
}


template <typename T>
T merge(T& left, T right) {
    T result;
    typename T::const_iterator it1 = left.begin();
    typename T::const_iterator it2 = right.begin();

    while (it1 != left.end() && it2 != right.end()) {
        if (*it1 < *it2) {
            result.push_back(*it1);
            ++it1;
        } else {
            result.push_back(*it2);
            ++it2;
        }
    }

    while (it1 != left.end()) {
        result.push_back(*it1);
        ++it1;
    }

    while (it2 != right.end()) {
        result.push_back(*it2);
        ++it2;
    }

    return result;
}

std::vector<int> fordJohnsonSortVector(const std::vector<int>& input) {
    if (input.size() <= 1) {
        return input;
    }

    std::vector<int> vec(input.begin(), input.end());

    std::vector<std::vector<int> > pairs;
    for (size_t i = 0; i + 1 < vec.size(); i += 2) {
        std::vector<int> pair;
        pair.push_back(vec[i]);
        pair.push_back(vec[i + 1]);
        if (pair[0] > pair[1]) {
       		 std::swap(pair[0], pair[1]);
   		 }
        pairs.push_back(pair);
    }

    if (vec.size() % 2 != 0) {
        std::vector<int> single;
        single.push_back(vec.back());
        pairs.push_back(single);
    }

    while (pairs.size() > 1) {
        std::vector<std::vector<int> > newPairs;
        for (size_t i = 0; i + 1 < pairs.size(); i += 2) {
            std::vector<int> merged = merge(pairs[i], pairs[i + 1]);
            newPairs.push_back(merged);
        }

        if (pairs.size() % 2 != 0) {
            newPairs.push_back(pairs.back());
        }

        pairs = newPairs;
    }

    return pairs.front();
}

// std::list<int> fordJohnsonSortList(const std::list<int>& input) {
//     if (input.size() <= 1) {
//         return input;
//     }

//     std::vector<int> vec(input.begin(), input.end());

//     std::vector<std::list<int> > pairs;
//     for (size_t i = 0; i + 1 < vec.size(); i += 2) {
//         std::list<int> pair;
//         pair.push_back(vec[i]);
//         pair.push_back(vec[i + 1]);
//         pair.sort();
//         pairs.push_back(pair);
//     }

//     if (vec.size() % 2 != 0) {
//         std::list<int> single;
//         single.push_back(vec.back());
//         pairs.push_back(single);
//     }

//     while (pairs.size() > 1) {
//         std::vector<std::list<int> > newPairs;
//         for (size_t i = 0; i + 1 < pairs.size(); i += 2) {
//             std::list<int> merged = merge(pairs[i], pairs[i + 1]);
//             newPairs.push_back(merged);
//         }

//         if (pairs.size() % 2 != 0) {
//             newPairs.push_back(pairs.back());
//         }

//         pairs = newPairs;
//     }

//     return pairs.front();
// }

std::list<int> fordJohnsonSortList(const std::list<int>& input) {
    if (input.size() <= 1) {
        return input;
    }

    std::list<std::list<int> > pairs;
    std::list<int>::const_iterator it = input.begin();
    while (it != input.end()) {
        std::list<int> pair;
        pair.push_back(*it);
        ++it;
        if (it != input.end()) {
            pair.push_back(*it);
            ++it;
        }
        pair.sort();
        pairs.push_back(pair);
    }

	std::cout << "Hello2\n";

    while (pairs.size() > 1) {
        std::list<std::list<int> > newPairs;
        std::list<std::list<int> >::iterator it = pairs.begin();
        while (it != pairs.end()) {
			std::list<std::list<int> >::iterator next_it = it;
			++next_it; // increment the copy, not the original iterator
			if (next_it != pairs.end()) {
				std::list<int> merged = merge(*it, *next_it);
				newPairs.push_back(merged);
				++it; // move to the next pair
			}
			if (it != pairs.end()) {
				++it; // skip the pair we just merged
			}
		}
        if (pairs.size() % 2 != 0) {
            newPairs.push_back(pairs.back());
        }
        pairs = newPairs;
    }

	std::cout << "Hello3\n";

    return pairs.front();
}

void PmergeMe::sort(std::string input)
{
	if (!verify_input(input))
		return;

	std::list<int> list;
	std::vector<int> vector;
	std::clock_t start;

	initialize_container(list, input);
	initialize_container(vector, input);

	std::cout << "Before:\t";
	print_container(list, 4);

	start = std::clock();
	list = fordJohnsonSortList(list);
	std::clock_t sortListTime = std::clock() - start;

	start = std::clock();
	vector = fordJohnsonSortVector(vector);
	std::clock_t sortVectorTime = std::clock() - start;

	std::cout << "After:\t";
	print_container(list, 4);

	std::cout << "After:\t";
	print_container(vector, 4);

	std::cout << "Time to process a range of " << list.size() << " elements with std::list : " << sortListTime << " us\n";
	std::cout << "Time to process a range of " << vector.size() << " elements with std::vector : " << sortVectorTime << " us\n";
}
