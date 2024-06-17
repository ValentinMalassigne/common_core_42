#include "Fixed.hpp"

// Constructors

Fixed::Fixed(void) : number(0)
{}

Fixed::Fixed(const Fixed& c_fixed)
{
	*this = c_fixed; 
}

Fixed::Fixed (const int c_int)
{
	number = c_int << binary_point;
}

Fixed::Fixed (const float c_float)
{
	number = static_cast<int>(roundf(c_float * (1 << binary_point)));
}

Fixed::~Fixed()
{}

// Operators

std::ostream& operator<<(std::ostream& os, const Fixed& fixed)
{
	os << fixed.toFloat();
	return os;
}

//arithmetic

Fixed &Fixed::operator=(const Fixed &other)
{
	if (this != &other)
		this->number = other.getRawBits();
	return *this;
}

Fixed Fixed::operator+(const Fixed &other)
{
	Fixed res;
	res.number = number + other.number;
	return res;
}

Fixed Fixed::operator-(const Fixed &other)
{
	Fixed res;
	res.number = number - other.number;
	return res;
}

Fixed Fixed::operator*(const Fixed &other)
{
	Fixed res;
	res.number = (static_cast <long long>(number) * other.number) >> binary_point;
	return res;
}

Fixed Fixed::operator/(const Fixed &other)
{
	Fixed res;
	res.number = (static_cast<long long>(number) << binary_point) / other.number;
	return res;
}

//comparison

bool Fixed::operator>(const Fixed &other) const
{
	return number > other.number;
}

bool Fixed::operator<(const Fixed &other) const
{
	return number < other.number;
}

bool Fixed::operator>=(const Fixed &other) const
{
	return number >= other.number;
}

bool Fixed::operator<=(const Fixed &other) const
{
	return number <= other.number;
}

bool Fixed::operator==(const Fixed &other) const
{
	return number == other.number;
}

bool Fixed::operator!=(const Fixed &other) const
{
	return number != other.number;
}

//increments

Fixed& Fixed::operator++()
{
	++number;
	return *this;
}

Fixed Fixed::operator++(int)
{
	Fixed temp(*this);
	++number;
	return temp;
}

Fixed& Fixed::operator--()
{
	--number;
	return *this;
}

Fixed Fixed::operator--(int)
{
	Fixed temp(*this);
	--number;
	return temp;
}

// Members functions

int Fixed::getRawBits( void ) const {
	return number;
}

void Fixed::setRawBits ( int const raw )
{
	number = raw;
}

float Fixed::toFloat( void ) const {
	return static_cast<float>(number) / (1 << binary_point);
}

int Fixed::toInt ( void ) const {
	return number >> binary_point;
}

Fixed Fixed::min(Fixed &fixed1, Fixed &fixed2)
{
	if (fixed1.number > fixed2.number)
		return fixed2;
	return fixed1;
}

Fixed const Fixed::min(const Fixed &fixed1,const Fixed &fixed2)
{
	if (fixed1.number > fixed2.number)
		return fixed2;
	return fixed1;
}

Fixed Fixed::max(Fixed &fixed1, Fixed &fixed2)
{
	if (fixed1.number > fixed2.number)
		return fixed1;
	return fixed2;
}

Fixed const Fixed::max(const Fixed &fixed1,const Fixed &fixed2)
{
	if (fixed1.number > fixed2.number)
		return fixed1;
	return fixed2;
}