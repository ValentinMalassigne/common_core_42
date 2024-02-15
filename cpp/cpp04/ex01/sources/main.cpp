#include "../headers/Animal.hpp"
#include "../headers/Cat.hpp"
#include "../headers/Dog.hpp"
#include <iostream>

void test_copy()
{
	Dog *dog1 = new Dog();
	Dog *dog2;

	dog1->getBrain()->saveIdea(0, "Bonjour\n");
	dog1->getBrain()->saveIdea(1, "Aurevoir\n");

	dog2 = new Dog(*dog1);

	std::cout << dog2->getBrain()->readIdea(0);
	std::cout << dog2->getBrain()->readIdea(1);

	delete dog1;
	delete dog2;
}

void test_array()
{
	Animal *animals[100];
	for(int i = 0; i < 50; i++)
		animals[i] = new Dog();
	for(int i = 50; i < 100; i++)
		animals[i] = new Cat();

	
	for(int i = 0; i < 100; i++)
		delete animals[i];
}


void subject_test()
{
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	delete j;//should not create a leak
	delete i;
}

int main()
{
	subject_test();
	// test_array();
	// test_copy();

	return 0;
}