#include "../headers/Base.hpp"
#include <iostream>
#include <cstdlib>
#include "../headers/A.hpp"
#include "../headers/B.hpp"
#include "../headers/C.hpp"

Base::~Base() {
}

Base* generate(void)
{
	srand(time(NULL));
	int random = rand() % 3;
	if (random == 0)
		return new A;
	else if (random == 1)
		return new B;
	else
		return new C;
}

void identify(Base* p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "C" << std::endl;
	else
		std::cout << "Unidentified Base class pointer" << std::endl;
}
/*
The function uses dynamic_cast to attempt to cast the Base pointer to pointers of types A, B, and C.
dynamic_cast is a special type of casting operator in C++ that is used for polymorphism, 
specifically for downcasting, which is the process of converting a pointer of a base class to a pointer of its derived class.

If the Base pointer is actually pointing to an object of type A, the dynamic_cast<A*>(p) will succeed
and return a valid pointer. 
If it's not, the dynamic_cast will return a null pointer,
*/

void identify(Base& p)
{
	try
	{
		A& a = dynamic_cast<A&>(p);
		(void)a;
		std::cout << "A" << std::endl;
		return ;
	}
	catch(std::exception& e)
	{}
	try
	{
		B& b = dynamic_cast<B&>(p);
		(void)b;
		std::cout << "B" << std::endl;
		return ;
	}
	catch(std::exception& e)
	{}
	try
	{
		C& c = dynamic_cast<C&>(p);
		(void)c;
		std::cout << "C" << std::endl;
		return ;
	}
	catch(std::exception& e)
	{}
	std::cout << "Unidentified Base class reference" << std::endl;
}
/*
The function uses dynamic_cast to attempt to cast the Base reference to a reference of type A.
dynamic_cast is a special type of casting operator in C++ that is used for polymorphism,
specifically for downcasting, which is the process of converting a reference of a base class
to a reference of its derived class.

If the Base reference is actually referring to an object of type A, the dynamic_cast<A&>(p)
will succeed and return a valid reference.
If it's not, the dynamic_cast will throw a std::bad_cast exception.
*/