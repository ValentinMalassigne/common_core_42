#pragma once
#include <stack>

template <typename T>
class MutantStack : public std::stack<T>
{
public:
		typedef typename std::stack<T>::container_type::iterator iterator;
		MutantStack();
		MutantStack(const MutantStack &other);
		MutantStack &operator=(const MutantStack& other);
		~MutantStack();

		iterator begin(void);
		iterator end(void);
};

template<typename T>
MutantStack<T>::MutantStack() {
};

template<typename T>
MutantStack<T>::MutantStack(MutantStack const& other) {
	*this = other;
}

template<typename T>
MutantStack<T>& MutantStack<T>::operator=(MutantStack const& other)
{
	std::stack<T>::operator=(other);
	return *this;
}

template<typename T>
MutantStack<T>::~MutantStack() {
};

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin() {
	return this->c.begin();
}

template<typename T>
typename MutantStack<T>::iterator MutantStack<T>::end() {
	return this->c.end();
};