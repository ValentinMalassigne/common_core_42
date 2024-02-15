#include "../headers/Animal.hpp"
#include "../headers/Cat.hpp"
#include "../headers/Dog.hpp"
#include "../headers/WrongAnimal.hpp"
#include "../headers/WrongCat.hpp"
#include <iostream>

void	testWrong(void)
{
	std::cout << "-- WrongAnimal" << std::endl;
	const WrongAnimal *	animal = new WrongAnimal();
	std::cout << "WrongAnimal type: " << animal->getType() << std::endl;
	animal->makeSound();
	delete animal;
	std::cout << std::endl;
	
	std::cout << "-- WrongCat by WrongCat class" << std::endl;
	const WrongCat *	cat1 = new WrongCat();
	std::cout << "WrongCat type: " << cat1->getType() << std::endl;
	cat1->makeSound();
	delete cat1;
	std::cout << std::endl;

	std::cout << "-- WrongCat by WrongAnimal parent class" << std::endl;
	const WrongAnimal * cat2 = new WrongCat();
	std::cout << "WrongAnimal type: " << cat2->getType() << std::endl;
	cat2->makeSound();
	delete cat2;
	std::cout << std::endl;
}

void	testCorrect(void)
{
	std::cout << "--- Correct Animal Cat Dog tests" << std::endl;
	std::cout << "-- Animal" << std::endl;
	const Animal *	animal = new Animal();
	std::cout << "Animal type: " << animal->getType() << std::endl;
	animal->makeSound();
	delete animal;
	std::cout << std::endl;

	std::cout << "-- Cat by cat class" << std::endl;
	const Cat *	cat1 = new Cat();
	std::cout << "Cat type: " << cat1->getType() << std::endl;
	cat1->makeSound();
	delete cat1;
	std::cout << std::endl;

	std::cout << "-- Cat by animal parent class" << std::endl;
	const Animal * cat2 = new Cat();
	std::cout << "Animal type: " << cat2->getType() << std::endl;
	cat2->makeSound();
	delete cat2;
	std::cout << std::endl;

	std::cout << "-- Dog by dog class" << std::endl;
	const Dog *	dog1 = new Dog();
	std::cout << "Dog type: " << dog1->getType() << std::endl;
	dog1->makeSound();
	delete dog1;
	std::cout << std::endl;

	std::cout << "-- Dog by animal parent class" << std::endl;
	const Animal * dog2 = new Dog();
	std::cout << "Animal type: " << dog2->getType() << std::endl;
	dog2->makeSound();
	delete dog2;
	std::cout << std::endl;

}

void test()
{
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;

	i->makeSound(); //will output the cat sound!
	j->makeSound();
	meta->makeSound();

	delete meta;
	delete j;
	delete i;
}

int main()
{
	// test();
	testWrong();
	// testCorrect();
	return 0;	
}