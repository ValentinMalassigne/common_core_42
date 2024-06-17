#include "../headers/Serializer.hpp"
#include "../headers/Data.hpp"
#include "iostream"

int main()
{
	Data *data = new Data(42, "John");
	uintptr_t raw = Serializer::serialize(data);
	data->age = 0;
	Data *data2 = Serializer::deserialize(raw);
	std::cout << "data2->age: " << data2->age << std::endl;
	std::cout << "data2->name: " << data2->name << std::endl;
	delete data;
	return 0;
}