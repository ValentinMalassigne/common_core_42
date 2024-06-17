#pragma once

#include <iostream>
#include <exception>

template <typename T>
class Array {
public:
	Array();
	Array(unsigned int n);
	Array(const Array<T> &other);
	~Array();

	Array<T> &operator=(const Array<T> &other);
	T &operator[](const unsigned int i);
	unsigned int size() const;

private:
	T *_array;
	unsigned int _size;
};
