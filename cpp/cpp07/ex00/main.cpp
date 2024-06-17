#include <iostream>
#include "whatever.hpp"

int main( void ) {
	int a = 2;
	int b = 3;
	::swap<int>( a, b );
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
	std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;
	std::string c = "chaine1";
	std::string d = "chaine2";
	::swap(c, d);
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
	std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;
	return 0;
}

// At compile time, based on how we use the function template in our function 
// calls, the compiler will decide to generate different type-specific versions
// of the function to be used at run-time (called template functions).  The 
// process is visualized below.
//
//
// double x = 10.6                           int m = 5;
// double y = 5.3;                           int n = 3;
//
// find_max(x,y)     <- Function Calls ->    find_max(m,n)
//              \                           /
//               \                         /
//                \                       /
//                 \                     /
//
//                  template <typename T>
//                  T find_max(T a, T b)
//  Function        {
//  Template ->       if (a > b) return a;
//                    else return b;
//                  }
//
//                 /               \
//                /                 \
//               /                   \
//              /                     \
//
// double find_max(double a,       int find_max(int a,
//                 double b)                    int b)
// {                               {
//   if (a > b) return a;            if (a > b) return a;
//   else return b;                  else return b;
// }                               }
//
//                \                  /
//                 Template Functions