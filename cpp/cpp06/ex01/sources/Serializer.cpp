#include "../headers/Serializer.hpp"

Serializer::Serializer()
{}

Serializer::Serializer(const Serializer &other)
{
	*this = other;
}

Serializer::~Serializer()
{}

Serializer& Serializer::operator=(const Serializer &other)
{
	(void) other;
	return *this;
}

uintptr_t Serializer::serialize(Data* ptr)
{
	return reinterpret_cast<uintptr_t>(ptr);
}
/*
The serialize method is using reinterpret_cast<uintptr_t> to cast the Data pointer ptr to an integer of type uintptr_t.
reinterpret_cast is a type of casting operator in C++ that converts one type to another,
even if the conversion would not normally be allowed.
In this case, it's being used to convert a pointer to an integer.
*/

Data* Serializer::deserialize(uintptr_t raw)
{
	return reinterpret_cast<Data*>(raw);
}