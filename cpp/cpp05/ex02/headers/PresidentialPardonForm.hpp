#pragma once

#include "AForm.hpp"
#include "Bureaucrat.hpp"

class PresidentialPardonForm : public AForm
{
public:
	PresidentialPardonForm();
	PresidentialPardonForm(const std::string target);
	PresidentialPardonForm(const PresidentialPardonForm &other);
	~PresidentialPardonForm();

	void execute(Bureaucrat const &executor) const;

	PresidentialPardonForm &operator=(const PresidentialPardonForm &other);
};