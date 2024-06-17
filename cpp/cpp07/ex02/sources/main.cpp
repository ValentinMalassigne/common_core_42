#include "../headers/Array.hpp"
#include "../templates/Array.tpp"
#include <iostream>

int main()
{
	//No parameter constructor
	std::cout << "No parameter constructor" << std::endl;
	Array<int> arr;
	std::cout << "arr1 size: " << arr.size() << std::endl;
	try
	{
		std::cout << "arr1[0]: " << arr[0] << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	

	//Parameter constructor
	std::cout << "Parameter constructor" << std::endl;
	int length = 5;
	Array<int> arr1(length);

	for(size_t i = 0; i < arr1.size(); i++)
		std::cout << "i = "<< i << " arr[i] = " << arr1[i] << std::endl;

	//Copy constructor
	std::cout << "Copy constructor" << std::endl;
	Array<int> arr2(arr1);

	for(size_t i = 0; i < arr2.size(); i++)
		std::cout << arr2[i] << std::endl;
	
	return 0;
}