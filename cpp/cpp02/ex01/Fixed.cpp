#include "Fixed.hpp"

Fixed::Fixed(void) : number(0)
{
	std::cout << "Default constructor called\n";
}

Fixed::Fixed(const Fixed& c_fixed)
{
	std::cout << "Copy constructor called\n";
	*this = c_fixed; 
}

Fixed::Fixed (const int c_int)
{
	std::cout << "Int constructor called\n";
	number = c_int << binary_point;
}

Fixed::Fixed (const float c_float)
{
	std::cout << "Float constructor called\n";
	number = static_cast<int>(roundf(c_float * (1 << binary_point)));
}

Fixed::~Fixed()
{
	std::cout << "Destructor called\n";
}

Fixed &Fixed::operator=(const Fixed &other)
{
	std::cout << "Copy assignment operator called\n";
	if (this != &other)
		this->number = other.getRawBits();
	return *this;
}

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

std::ostream& operator<<(std::ostream& os, const Fixed& fixed)
{
	os << fixed.toFloat();
	return os;
}