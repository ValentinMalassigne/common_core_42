#pragma once
#include <string>

class Data {
public:
	Data();
	Data(const int c_age, const std::string c_name);
	Data(const Data &other);
	~Data();

	Data& operator=(const Data &other);

	int age;
	std::string name;
};