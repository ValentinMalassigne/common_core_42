#pragma once

#include <exception>
#include <vector>

class Span
{
public:
	Span();
	Span(unsigned int N);
	Span(const Span &other);
	~Span();

	Span &operator=(const Span &other);

	void addNumber(int number);
	void addNumbers(std::vector<int>::iterator first, std::vector<int>::iterator last);

	unsigned int shortestSpan();
	unsigned int longestSpan();

	class NoSpanException : public std::exception
	{
		virtual const char *what() const throw();
	};

	class SpanIsFullException : public std::exception
	{
		virtual const char *what() const throw();
	};

private:
	unsigned int _N;
	std::vector<int> _numbers;
};