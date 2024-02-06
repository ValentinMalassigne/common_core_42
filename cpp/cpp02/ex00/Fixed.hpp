#pragma once

#include <iostream>

class Fixed {
public:
	Fixed(void);
	Fixed(const Fixed& c_fixed);
	~Fixed();
	Fixed &operator=(const Fixed &other);

	int getRawBits ( void ) const;
	void setRawBits ( int const raw );
private:
	int number;
	static const int binary_point = 8;
};