#include "../headers/PresidentialPardonForm.hpp"
#include <iostream>
#include <fstream>

PresidentialPardonForm::PresidentialPardonForm() : AForm("default PresidentialPardonForm", 25, 5)
{
}

PresidentialPardonForm::PresidentialPardonForm(const std::string c_target) : AForm("default PresidentialPardonForm", 25, 5)
{
	setTarget(c_target);
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &other)
{
	*this = other;
}

PresidentialPardonForm::~PresidentialPardonForm()
{
}

PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &other)
{
	if (this != &other)
		setTarget(other.getTarget());
	return *this;
}

void PresidentialPardonForm::execute(Bureaucrat const &executor) const
{
	if (executor.getGrade() > getMinGradeToExecute())
		throw AForm::GradeTooLowException();
	if (getIsSigned() == false)
		throw AForm::FormNotSignedException();
	std::cout << getTarget() << " has been pardoned by Zaphod Beeblebrox.\n";
}