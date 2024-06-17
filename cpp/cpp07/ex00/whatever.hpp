#pragma once

template <typename T>
	static T max(T a, T b) {
		return (a > b) ? a : b;
	}

template <typename T>
	static T min(T a, T b) {
		return (a < b) ? a : b;
	}

template <typename T>
	static void swap(T &a, T &b) {
		T tmp = a;
		a = b;
		b = tmp;
	}

/*
The template prefix defines a template paramater T
We can know instantiate the class with a type : utils<int> or utils<float>, etc.
The compiler will generate the appropriate classes for the provided type.

We can also add several template parameters : template <typename T, int length>
And the value of length can be used in the class definition.
We would instantiate the class with utils<int, 42> for example.
The values needs to be known at compile time.
*/