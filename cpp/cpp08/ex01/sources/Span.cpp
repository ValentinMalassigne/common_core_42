#include "../headers/Span.hpp"

Span::Span() : _N(0)
{
}

Span::Span(unsigned int N) : _N(N)
{
}

Span::Span(const Span &other)
{
	*this = other;
}

Span::~Span()
{
}

Span &Span::operator=(const Span &other)
{
	if (this != &other)
	{
		_N = other._N;
		_numbers = other._numbers;
	}
	return *this;
}

void Span::addNumber(int number)
{
	if (_numbers.size() >= _N)
		throw Span::SpanIsFullException();
	_numbers.push_back(number);
}

void Span::addNumbers(std::vector<int>::iterator first, std::vector<int>::iterator last)
{
	for (std::vector<int>::iterator it = first; it != last; ++it)
		addNumber(*it);
}

unsigned int Span::shortestSpan()
{
	if (_numbers.size() <= 1)
		throw Span::NoSpanException();
	std::vector<int> sorted = _numbers;
	std::sort(sorted.begin(), sorted.end());
	unsigned int shortest = UINT_MAX;
	for (size_t i = 1; i < sorted.size(); i++)
	{
		unsigned int span = sorted[i] - sorted[i - 1];
		if (span < shortest)
			shortest = span;
	}
	return shortest;
}

unsigned int Span::longestSpan()
{
	if (_numbers.size() <= 1)
		throw Span::NoSpanException();
	std::vector<int> sorted = _numbers;
	std::sort(sorted.begin(), sorted.end());
	return sorted.back() - sorted.front();
}

const char *Span::NoSpanException::what() const throw()
{
	return "No span to find";
}

const char *Span::SpanIsFullException::what() const throw()
{
	return "Span is full";
}