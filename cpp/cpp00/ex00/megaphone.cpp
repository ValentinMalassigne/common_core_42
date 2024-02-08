#include <iostream>

class Megaphone {
public:
	std::string input;

	void speakLoudly()
	{
		std::string output = "";

		for(size_t i = 0; i < input.length(); i++){
			output += toupper(input[i]);
		}
		std::cout << output << std::endl;
	}
};

int main (int argc, char **argv) {
	Megaphone megaphone;
	
	megaphone.input="";
	if (argc < 2)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	} else {
		argv++;
		while (*argv)
		{
			megaphone.input.append(*argv);
			argv++;
		}
		megaphone.speakLoudly();
	}
	return 0;
}