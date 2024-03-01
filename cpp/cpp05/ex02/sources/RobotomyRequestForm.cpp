#include "../headers/RobotomyRequestForm.hpp"
#include <iostream>
#include <fstream>

RobotomyRequestForm::RobotomyRequestForm() : AForm("default RobotomyRequestForm", 72, 45)
{
}

RobotomyRequestForm::RobotomyRequestForm(const std::string c_target) : AForm("default RobotomyRequestForm", 72, 45)
{
	setTarget(c_target);
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other)
{
	*this = other;
}

RobotomyRequestForm::~RobotomyRequestForm()
{
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &other)
{
	if (this != &other)
		setTarget(other.getTarget());
	return *this;
}

void RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
	if (executor.getGrade() > getMinGradeToExecute())
		throw AForm::GradeTooLowException();
	if (getIsSigned() == false)
		throw AForm::FormNotSignedException();
	std::cout << getName() << " is making some drilling noises\n";
	srand((unsigned int)time(NULL));
	int v1 = rand() % 2;
	if (v1 == 0)
		std::cout << getTarget() << " has been robotomized successfully.\n";
	else
		std::cout << getTarget() << " robotomization has failed.\n";
}