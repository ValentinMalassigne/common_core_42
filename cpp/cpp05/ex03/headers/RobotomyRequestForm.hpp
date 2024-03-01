#pragma once

#include "AForm.hpp"
#include "Bureaucrat.hpp"

class RobotomyRequestForm : public AForm
{
public:
	RobotomyRequestForm();
	RobotomyRequestForm(const std::string target);
	RobotomyRequestForm(const RobotomyRequestForm &other);
	~RobotomyRequestForm();

	void execute(Bureaucrat const &executor) const;

	RobotomyRequestForm &operator=(const RobotomyRequestForm &other);
};