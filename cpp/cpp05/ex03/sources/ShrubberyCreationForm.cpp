#include "../headers/ShrubberyCreationForm.hpp"
#include <iostream>
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("default ShrubberyCreationForm", 145, 137)
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string c_target) : AForm("default ShrubberyCreationForm", 145, 137)
{
	setTarget(c_target);
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other)
{
	*this = other;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other)
{
	if (this != &other)
		setTarget(other.getTarget());
	return *this;
}

void ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
	if (executor.getGrade() > getMinGradeToExecute())
		throw AForm::GradeTooLowException();
	if (getIsSigned() == false)
		throw AForm::FormNotSignedException();

	std::ofstream outfile(getTarget());

	outfile << "          &&& &&  & &&\n"
			   "      && &\\/&\\|& ()|/ @, &&\n"
			   "      &\\/(/&/&||/& /_/)_&/_&\n"
			   "   &() &\\/&|()|/&\\/ '%\" & ()\n"
			   "  &_\\_&&_\\ |& |&&/&__%_/_& &&\n"
			   "&&   && & &| &| /& & % ()& /&&\n"
			   " ()&_---()&\\&\\|&&-&&--%---()~\n"
			   "     &&     \\|||\n"
			   "             |||\n"
			   "             |||\n"
			   "             |||\n"
			   "       , -=-~  .-^- _\n"
			<< std::endl;

	outfile << "          &&& &&  & &&\n"
			   "      && &\\/&\\|& ()|/ @, &&\n"
			   "      &\\/(/&/&||/& /_/)_&/_&\n"
			   "   &() &\\/&|()|/&\\/ '%\" & ()\n"
			   "  &_\\_&&_\\ |& |&&/&__%_/_& &&\n"
			   "&&   && & &| &| /& & % ()& /&&\n"
			   " ()&_---()&\\&\\|&&-&&--%---()~\n"
			   "     &&     \\|||\n"
			   "             |||\n"
			   "             |||\n"
			   "             |||\n"
			   "       , -=-~  .-^- _\n"
			<< std::endl;

	outfile.close();
}