#include <iostream>
#include <fstream>

void usage_message()
{
	std::cout << "Usage : ./Sed_is_for_losers filename string1 string2\nOpens filename and replace string1 occurences with string2\n";
}

bool are_inputs_valid(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cout << "Invalid number of arguments\n";
		usage_message();
		return (false);
	}
	else if (!argv || !argv[1] || !(argv[2]) || !(argv[3]))
	{
		std::cout << "Invalid argument\n";
		usage_message();
		return (false);
	}
	return (true);
}

void replace_values(std::string& fileContent, char **argv)
{
	std::string to_replace = argv[2];
	std::string replacement = argv[3];
	size_t position;
	int to_replace_length = to_replace.length();
	int replacement_length = replacement.length();
	size_t i = 0;

	while (i < fileContent.length())
	{
		position = fileContent.find(to_replace);
	    if (position != std::string::npos) {
			fileContent.erase(position, to_replace_length);
			fileContent.insert(position, replacement);
			i += replacement_length;
    	} else
			i++;
	}
}

bool read_file_content(std::string& fileContent, char *path)
{
	std::ifstream inputFile;
	std::string line;

	inputFile.open(path);
	if (inputFile.is_open())
	{
		while (std::getline(inputFile, line))
			fileContent.append(line).append("\n");
		fileContent.erase(fileContent.length() - 1, 1);
	} else {
		std::cout << "Error while trying to open " << *path << std::endl;
		inputFile.close();
		return false;
	}
	inputFile.close();
	return true;
}

void write_content_in_file(std::string fileContent, char *path)
{
	std::ofstream outputFile;
	outputFile.open(path);
	if (outputFile.is_open())
		outputFile << fileContent;
	else
		std::cout << "Error while trying to open " << *path << std::endl;
	outputFile.close();
}

void manage_file(char **argv)
{
	std::string fileContent;

	if (!read_file_content(fileContent, argv[1]))
		return ;
	replace_values(fileContent, argv);
	write_content_in_file(fileContent, argv[1]);
}

int main(int argc, char **argv)
{
	if (are_inputs_valid(argc, argv) == false)
		return (0);
	manage_file(argv);
	return (0);
}