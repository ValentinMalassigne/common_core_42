#pragma once

#include <algorithm>
#include <iostream>
#include <sstream>

template <typename T>
int easyfind(T &container, int n)
{
	typename T::iterator it = std::find(container.begin(), container.end(), n);
	if (it == container.end())
	{
		std::ostringstream oss;
		oss << n;
    	std::string str = oss.str();
		throw std::runtime_error(std::string("Element ") + str +" not found");
	}
	return *it;
}

/*
In C++, an "int container" typically refers to a data structure that holds integer values.
It can be implemented using various data structures, such as arrays, vectors, lists.

In C++, an iterator is an object that allows traversal through the elements of a container
(such as an array, vector, list, etc.) and provides a way to access and manipulate those elements.
Iterators provide a uniform interface for iterating over different types of containers, abstracting
away the underlying implementation details of the container.

Examples of containers with iterators :

1) std::vector: A dynamic array that can grow and shrink in size.

#include <vector>

std::vector<int> vec;
vec.push_back(1);
vec.push_back(2);
vec.push_back(3);

std::vector<int> vec = {1, 2, 3};
for(std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
	std::cout << *it << std::endl;
}

2) std::list: A doubly-linked list that allows fast insertion and deletion of elements at any position.

#include <list>

std::list<int> lst;
lst.push_back(1);
lst.push_back(2);
lst.push_back(3);

std::list<int> lst = {1, 2, 3};
for(std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
	std::cout << *it << std::endl;
}

3) std::deque: A double-ended queue that allows fast insertion and deletion of elements at both ends.

#include <deque>

std::deque<int> deq;
deq.push_back(1);
deq.push_front(2);

std::deque<int> deq = {1, 2, 3};
for(std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it) {
	std::cout << *it << std::endl;
}

4) std::set: A container that stores unique elements in sorted order.

#include <set>

std::set<int> st;
st.insert(1);
st.insert(2);
st.insert(3);

std::set<int> st = {1, 2, 3};
for(std::set<int>::iterator it = st.begin(); it != st.end(); ++it) {
	std::cout << *it << std::endl;
}

5) std::map: A container that stores key-value pairs in sorted order based on the key.

#include <map>

std::map<int, std::string> mp;
mp[1] = "one";
mp[2] = "two";
mp[3] = "three";

std::map<int, std::string> mp = {{1, "one"}, {2, "two"}, {3, "three"}};
for(std::map<int, std::string>::iterator it = mp.begin(); it != mp.end(); ++it) {
	std::cout << it->first << " => " << it->second << std::endl;
}

For 6 / 7 / 8 :
These containers do not support iterators in the traditional sense because they are designed
to provide only restricted access to their elements (LIFO or FIFO). However, if you need to
iterate over their elements, you would typically have to pop elements one by one until the
container is empty.

When you use certain container adapters like std::stack, std::queue, and std::priority_queue,
they internally use other containers as their underlying data storage. These underlying
containers provide the actual storage and operations for the adapter.

6) std::stack: A container that provides LIFO (Last In First Out) access to elements.

#include <stack>

std::stack<int> stk;
stk.push(1);
stk.push(2);
stk.push(3);

7) std::queue: A container that provides FIFO (First In First Out) access to elements.

#include <queue>

std::queue<int> que;
que.push(1);
que.push(2);
que.push(3);

8) std::priority_queue: A container that provides access to elements based on priority.

#include <queue>

std::priority_queue<int> pq;
pq.push(1);
pq.push(2);
pq.push(3);

*/
