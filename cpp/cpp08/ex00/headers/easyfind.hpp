#pragma once

#include <algorithm>

template <typename T>
int easyfind(T &container, int n)
{
	typename T::iterator it = std::find(container.begin(), container.end(), n);
	if (it == container.end())
		throw std::exception();
	return *it;
}

/*
In C++, an "int container" typically refers to a data structure that holds integer values.
It can be implemented using various data structures, such as arrays, vectors, lists.

In C++, an iterator is an object that allows traversal through the elements of a container 
(such as an array, vector, list, etc.) and provides a way to access and manipulate those elements.
Iterators provide a uniform interface for iterating over different types of containers, abstracting
away the underlying implementation details of the container.
*/