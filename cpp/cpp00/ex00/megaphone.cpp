#include <iostream>
#include <cctype>

int main(int argc, char **argv) {
	// int i;
	std::string newString;

	if (argc == 1)
		return (1);

	argv++;
	newString += std::toupper(**argv);
	std::cout << std::toupper(**argv);
	
	// if (argc == 1)
    // 	std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	// else if (argc > 1)
	// {
	// 	argv++;
	// 	while (*argv)
	// 	{
	// 		i = 0;
	// 		newString.clear();
	// 		while (*argv[i])
	// 		{
	// 			newString += std::toupper(*argv[i]);
	// 			i++;
	// 		}
	// 		std::cout << newString;
	// 		argv++;
	// 	}
	// 	std::cout << std::endl;
	// }
    return 0;
}