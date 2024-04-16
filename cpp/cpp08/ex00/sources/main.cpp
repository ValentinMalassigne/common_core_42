#include "../headers/easyfind.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <deque>

int main()
{
	std::vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);

	std::list<int> lst;
	lst.push_back(1);
	lst.push_back(5);
	lst.push_back(3);

	std::deque<int> deq;
	deq.push_back(1);
	deq.push_front(2);

	int to_find = 2;
	try
	{
		std::cout << "Search " << to_find << " in vec ... " << easyfind(vec, to_find) << " found !\n";
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		std::cout << "Search " << to_find << " in lst ... " << easyfind(lst, to_find) << " found !\n";
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		std::cout << "Search " << to_find << " in deq ... " << easyfind(deq, to_find) << " found !\n";
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}