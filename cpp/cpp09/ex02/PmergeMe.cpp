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

void mergeList(std::list<int> &left, std::list<int> &right, std::back_insert_iterator<std::list<int> > result)
{
	while (!left.empty() && !right.empty())
	{
		if (left.front() < right.front())
		{
			*result = left.front();
			left.pop_front();
		}
		else
		{
			*result = right.front();
			right.pop_front();
		}
		++result;
	}

	while (!left.empty())
	{
		*result = left.front();
		left.pop_front();
		++result;
	}

	while (!right.empty())
	{
		*result = right.front();
		right.pop_front();
		++result;
	}
}

void mergeSortList(std::list<int> &lst)
{
	size_t size = lst.size();
	if (size <= 1)
		return;

	std::list<int> left;
	std::list<int> right;

	std::list<int>::iterator middle = lst.begin();
	std::advance(middle, size / 2);

	left.splice(left.begin(), lst, lst.begin(), middle);
	right.splice(right.begin(), lst, middle, lst.end());

	mergeSortList(left);
	mergeSortList(right);

	lst.clear();
	mergeList(left, right, std::back_inserter(lst));
}

void mergeVector(std::vector<int> left, std::vector<int> right, std::vector<int> &vector)
{
	size_t leftIndex = 0;
	size_t rightIndex = 0;
	size_t vectorIndex = 0;

	while (leftIndex < left.size() && rightIndex < right.size())
	{
		if (left[leftIndex] < right[rightIndex])
		{
			vector[vectorIndex] = left[leftIndex];
			leftIndex++;
		}
		else
		{
			vector[vectorIndex] = right[rightIndex];
			rightIndex++;
		}
		vectorIndex++;
	}
	while (leftIndex < left.size())
	{
		vector[vectorIndex] = left[leftIndex];
		leftIndex++;
		vectorIndex++;
	}
	while (rightIndex < right.size())
	{
		vector[vectorIndex] = right[rightIndex];
		rightIndex++;
		vectorIndex++;
	}
}

static void mergeSortVector(std::vector<int> &vector)
{
	size_t size = vector.size();
	if (size <= 1)
		return;

	size_t middle = size / 2;
	std::vector<int> left;
	std::vector<int> right;

	for (size_t i = 0; i < middle; i++)
		left.push_back(vector[i]);

	for (size_t i = middle; i < size; i++)
		right.push_back(vector[i]);

	mergeSortVector(left);
	mergeSortVector(right);

	mergeVector(left, right, vector);
}

template <typename T>
static void initialize_container(T &res, std::string input)
{
	std::string number = "";

	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] == ' ')
		{
			res.push_back(std::stoi(number));
			number = "";
		}
		else
			number += input[i];
	}
	res.push_back(std::stoi(number));
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
	mergeSortList(list);
	std::clock_t sortListTime = std::clock() - start;

	start = std::clock();
	mergeSortVector(vector);
	std::clock_t sortVectorTime = std::clock() - start;

	std::cout << "After:\t";
	print_container(list, 4);

	// std::cout << "After:\t";
	// print_container(vector, 4);

	std::cout << "Time to process a range of " << list.size() << " elements with std::list : " << sortListTime << " us\n";
	std::cout << "Time to process a range of " << vector.size() << " elements with std::vector : " << sortVectorTime << " us\n";
}
