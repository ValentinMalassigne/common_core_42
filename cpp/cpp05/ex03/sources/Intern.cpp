#include "../headers/Intern.hpp"
#include "../headers/ShrubberyCreationForm.hpp"
#include "../headers/RobotomyRequestForm.hpp"
#include "../headers/PresidentialPardonForm.hpp"

Intern::Intern()
{
}

Intern::Intern(const Intern &other)
{
	*this = other;
}

Intern::~Intern()
{
}

Intern &Intern::operator=(const Intern &other)
{
	(void)other;
	return (*this);
}

static AForm *makeShrubbery(const std::string formTarget)
{
	return new ShrubberyCreationForm(formTarget);
}

static AForm *makeRobotomy(const std::string formTarget)
{
	return new RobotomyRequestForm(formTarget);
}

static AForm *makePresidential(const std::string formTarget)
{
	return new PresidentialPardonForm(formTarget);
}

AForm *Intern::makeForm(const std::string formName, const std::string formTarget) const
{
	AForm *res = NULL;

	const std::string formNames[3] = {"shrubbery creation", "robotomy request", "presidential pardon"};

	AForm *(*makeFormFunctions[3])(const std::string formTarget) = {
		&makeShrubbery,
		&makeRobotomy,
		&makePresidential,
	};

	for (int i = 0; i < 3; i++)
	{
		if (formName == formNames[i])
		{
			std::cout << "Intern creates " << formName << std::endl;
			res = makeFormFunctions[i](formTarget);
			return res;
		}
	}

	std::cerr << "Intern could not create " << formName << " reason : form does not exists.\n";
	return res;
}