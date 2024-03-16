#pragma once

#include <stdint.h>
#include "Data.hpp"

class Serializer {
private:
	Serializer();
	Serializer(const Serializer &other);
	~Serializer();

	Serializer &operator=(const Serializer &other);

public:
	static uintptr_t serialize(Data* ptr);
	static Data* deserialize(uintptr_t raw);
};
/*
Serialization is commonly used in scenarios such as saving the state 
of an object to disk, sending objects across a network, or caching data.
*/