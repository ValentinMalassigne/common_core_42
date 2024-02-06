#pragma once

#include <iostream>
#include <cmath>

class Fixed {
public:
	Fixed(void);
	Fixed(const Fixed& c_fixed);
	Fixed(const int c_int);
	Fixed(const float c_float);
	~Fixed();
	
	Fixed &operator=(const Fixed &other);
	Fixed operator+(const Fixed &other);
	Fixed operator-(const Fixed &other);
	Fixed operator*(const Fixed &other);
	Fixed operator/(const Fixed &other);

	bool operator>(const Fixed& other) const;
	bool operator<(const Fixed& other) const;
	bool operator>=(const Fixed &other) const;
	bool operator<=(const Fixed &other) const;
	bool operator==(const Fixed &other) const;
	bool operator!=(const Fixed &other) const;

	Fixed& operator++();
	Fixed operator++(int);
	Fixed& operator--();
	Fixed operator--(int);

	int getRawBits ( void ) const;
	void setRawBits ( int const raw );
	float toFloat( void ) const;
	int toInt ( void ) const;

	static Fixed min(Fixed &fixed1, Fixed &fixed2);
	static Fixed min(const Fixed &fixed1, const Fixed &fixed2);
	static Fixed max(Fixed &fixed1, Fixed &fixed2);
	static Fixed max(const Fixed &fixed1, const Fixed &fixed2);
private:
	int number;
	static const int binary_point = 8;
};

std::ostream& operator<<(std::ostream& os, const Fixed& fixed);