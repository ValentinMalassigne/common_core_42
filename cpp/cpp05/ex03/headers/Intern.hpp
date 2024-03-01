#pragma once

#include "AForm.hpp"

class Intern
{
public:
	Intern();
	Intern(const Intern &other);
	~Intern();

	Intern &operator=(const Intern &other);

	AForm *makeForm(const std::string formName, const std::string formTarget) const;
};