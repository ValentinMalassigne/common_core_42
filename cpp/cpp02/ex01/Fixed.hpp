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

	int getRawBits ( void ) const;
	void setRawBits ( int const raw );
	float toFloat( void ) const;
	int toInt ( void ) const;
private:
	int number;
	static const int binary_point = 8;
};

std::ostream& operator<<(std::ostream& os, const Fixed& fixed);