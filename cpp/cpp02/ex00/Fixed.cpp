#include "Fixed.hpp"

Fixed::Fixed(void) : number(0)
{
	std::cout << "Default constructor called\n";
}

Fixed::Fixed(const Fixed &c_fixed)
{
	std::cout << "Copy constructor called\n";
	number = c_fixed.getRawBits();
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
	std::cout << "getRawBits member function called\n";
	return number;
}

void Fixed::setRawBits ( int const raw )
{
	number = raw;
}