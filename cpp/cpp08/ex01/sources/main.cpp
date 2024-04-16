#include "../headers/Span.hpp"
#include <iostream>

int main()
{
	std::cout << "Subject test" << std::endl;

	try
	{
		Span sp = Span(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);

		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << "----------------" << std::endl;
	std::cout << "Test with 10000 random numbers" << std::endl;

	int SIZE = 10000;

	try
	{
		Span sp2 = Span(SIZE);

		std::vector<int> vec;
		srand(time(NULL));
		for (int i = 0; i < SIZE; i++)
			vec.push_back(rand());
		sp2.addNumbers(vec.begin(), vec.end());

		std::cout << sp2.shortestSpan() << std::endl;
		std::cout << sp2.longestSpan() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}