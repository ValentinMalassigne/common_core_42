/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpothin <cpothin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:36:49 by acharlot          #+#    #+#             */
/*   Updated: 2024/03/25 17:15:27 by cpothin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/ircserv.hpp"

bool searchString(const char* mainString, const char* subString)
{
    int mainLength = strlen(mainString);
    int subLength = strlen(subString);
    for (int i = 0; i <= mainLength - subLength; ++i) {
        if (strncmp(mainString + i, subString, subLength) == 0)
            return true;
    }
    return false;
}
/*
    To trim the spaces before and after a string.
*/
void trim(std::string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    if (first == std::string::npos || last == std::string::npos)
        str = "";
    else
        str = str.substr(first, last - first + 1);
}

bool isFileEmpty(const std::string& filename)
{
    std::ifstream file(filename.c_str(), std::ios::ate);
    return file.tellg() == 0;
}

/*
    This function will create a new string and return it.
*/
std::string ToUpper(std::string str)
{
    for (size_t i = 0; i < str.size(); i++)
		str[i] = std::toupper(str[i]);
    return (str);
}

/*
    Removes quotes in a string.
*/
void removeQuotes(std::string &str)
{
    size_t pos = 0;
    while ((pos = str.find("\"", pos)) != std::string::npos) {
        str.erase(pos, 1);
    }
}

std::string formatNumber(double number)
{
    std::ostringstream oss;
    int precision = number == static_cast<int>(number) ? 0 : 2;
    if (precision == 2)
        oss << std::fixed << std::setprecision(2) << number;
    else
        oss << static_cast<int>(number);
    std::string result = oss.str();
    size_t pointPos = result.find('.');
    if (pointPos == std::string::npos)
        pointPos = result.size();
    for (int i = pointPos - 3; i > 0; i -= 3)
        result.insert(i, ",");
    return result;
}

static void FirstAnswer(Server *server, int const client_fd, Client &client)
{
    std::string bot = BOT_NAME;
    
    addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), "Hello !"));
    addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), "I am the spirit of Mr Rault."));
    addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), "Ask me anything about geography."));
    addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), "Commands are:"));
    addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), "- " + TEAL + "HELP" + RESET + " -> Can I help you?"));
    addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), "- " + TEAL + "RANDOM" + RESET + " -> To get a random sentence."));
    addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), "- " + TEAL + "JOKE" + RESET + " -> To get a random programming joke."));
    addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), "- " + TEAL + "QUIZZ" + RESET + " -> I'll ask a question and you'll have to answer!"));
    addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), "- " + TEAL + "QUIZZ <ANY COUNTRY> <POPULATION/CAPITAL/LEADER/AREA>" + RESET + " -> To give you some informations about <any country>."));
    addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), "------------------------------------------"));
    client.bot_question.firstTime = true;
}

static void	botQuizz(Server *server, int const client_fd, Client &client, std::string &msg)
{
    std::string bot = BOT_NAME;
    s_cmd cmd_infos;
    cmd_infos.name = "PRIVMSG";
    cmd_infos.prefix = "Prefix";
    std::ifstream file("src/utils/bot.csv");
    std::string line;
    std::stringstream ss0;
    int rand1 = rand() % 192;
    int rand2 = rand() % 192;
    while (rand2 == rand1)
        rand2 = rand() % 192;
    int nbRand = 0;
    if (!file.is_open())
	{
        ErrMsg("Error: file does not exist");
        return ;
    }
    if (isFileEmpty("src/utils/bot.csv"))
	{
        ErrMsg("Error: file is empty");
        return ;
    }
    int foundWords = 0;
    while (std::getline(file, line))
    {
        std::string country, city, monarch;
        double area;
        int population;
        char comma;
        std::stringstream ss(line);
        if (std::getline(ss, country, ',') && std::getline(ss, city, ',') && ss >> area >> comma
        && ss >> population >> comma && std::getline(ss, monarch, ','))
        {
            trim(country);
            trim(city);
            trim(monarch);
            removeQuotes(country);
            removeQuotes(city);
            removeQuotes(monarch);
            if (nbRand == rand1)
            {
                client.bot_question.area1 = area;
                client.bot_question.capital1 = city;
                client.bot_question.country1 = country;
                client.bot_question.pop1 = population;
                client.bot_question.president1 = monarch;
            }
            else if (nbRand == rand2)
            {
                client.bot_question.area2 = area;
                client.bot_question.capital2 = city;
                client.bot_question.country2 = country;
                client.bot_question.pop2 = population;
                client.bot_question.president2 = monarch;
            }
            if (searchString(msg.c_str(), ToUpper(country).c_str()))
            {
                foundWords++;
                if (searchString(msg.c_str(), "POPULATION"))
                {
                    foundWords++;
                    ss0 << TEAL << country << RESET << " has " << GREEN << formatNumber(population) << RESET << " inhabitants.\n";
                    addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), ss0.str()));
                }
                if (searchString(msg.c_str(), "PRESIDENT") || searchString(msg.c_str(), "MONARCH") || searchString(msg.c_str(), "LEADER") || searchString(msg.c_str(), "KING") || searchString(msg.c_str(), "QUEEN"))
                {
                    foundWords++;
                    ss0.str("");
                    ss0 << "The leader of " << TEAL << country << RESET << " is " << GREEN << monarch << RESET << ".\n";
                    addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), ss0.str()));
                }
                if (searchString(msg.c_str(), "AREA"))
                {
                    foundWords++;
                    ss0.str("");
                    ss0 << "The area of " << TEAL << country << RESET << " is " << GREEN << formatNumber(area) << RESET << " Km².\n";
                    addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), ss0.str()));
                }
                if (searchString(msg.c_str(), "CAPITAL") || searchString(msg.c_str(), "CITY"))
                {
                    foundWords++;
                    ss0.str("");
                    ss0 << "The capital of " << TEAL << country << RESET << " is " << GREEN << city << RESET << ".\n";
                    addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), ss0.str()));
                }
                cmd_infos.message = ss0.str();
                if (foundWords == 1)
                    addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), "Ask informations about " + TEAL + country + RESET + ": Population, area, capital, leader."));
            }
        }
        else
            std::cerr << "Error parsing line: " << line << std::endl;
        nbRand++;
    }
    if (foundWords == 0)
    {
        trim(msg);
        if (msg != ":QUIZZ")
        {
            addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), "I don't understand your question."));
            addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), "Please type \"quizz\" to get a random question or \"quizz <any country>\" to get informations about a country."));
            return;
        }
        int randomValue = rand() % 4 + 1;
        client.bot_question.questionType = (QuestionType)randomValue;
        switch (client.bot_question.questionType)
        {
            case Capital:
                addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), "What is the capital of " + TEAL + client.bot_question.country1 + RESET + "?"));
                client.bot_question.answer = client.bot_question.capital1;
            break;
            case President:
                addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), "Who is the leader of " + TEAL + client.bot_question.country1 + RESET + "?"));
                client.bot_question.answer = client.bot_question.president1;
            break;
            case LargerArea:
                addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), "Which country has the largest area? " + TEAL + client.bot_question.country1 + RESET + " or " + TEAL + client.bot_question.country2 + RESET + "?"));
                client.bot_question.answer = client.bot_question.area1 > client.bot_question.area2 ? client.bot_question.country1 : client.bot_question.country2;
            break;
            case MostPopulated:
                addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), "Which country is the most populated? " + TEAL + client.bot_question.country1 + RESET + " or " + TEAL + client.bot_question.country2 + RESET + "?"));
                client.bot_question.answer = client.bot_question.pop1 > client.bot_question.pop2 ? client.bot_question.country1 : client.bot_question.country2;
            break;
            default:
            break;
        }
    }
}

/*
    Prototype for the command => `/msg raultbot: joke`
*/
static void	botJoke(Server *server, int const client_fd, Client &client, std::string &bot)
{
	int index = rand() % 81;
	
	std::string str;
	switch (index)
	{
        case 0: str = "Why don't scientists trust atoms? Because they make up everything."; break;
        case 1: str = "You are the ; to my statements."; break;
        case 2: str = "Why did the programmer quit her job? Because she didn’t get arrays."; break;
        case 3: str = "What did the Java Code say to the C code? You’ve got no class."; break;
        case 4: str = "A programmer puts two glasses on his bedside table before going to sleep. A full one, in case he gets thirsty, and an empty one, in case he doesn’t."; break;
        case 5: str = "Why do programmers prefer dark mode? Because light attracts bugs."; break;
        case 6: str = "Binary: It’s as easy as 01, 10, 11."; break;
        case 7: str = "All programmers are playwrights, and all computers are lousy actors."; break;
        case 8: str = "Algorithm: words used by programmers when they don’t want to explain what they did."; break;
        case 9: str = "When in doubt // it out"; break;
        case 10: str = "An optimist says: ‘The Glass if Half-Full.’ A pessimist says: ‘The Glass if Half-Empty.’ A programmer says: ‘The Glass is Twice as Large as Necessary’."; break;
        case 11: str = "A good programmer is someone who looks both ways before crossing a one-way street."; break;
        case 12: str = "A user interface is like a joke. If you have to explain it, it means it’s not good."; break;
        case 13: str = "Things aren’t always #000000 and #FFFFFF."; break;
        case 14: str = "Why do Java programmers have to wear glasses? Because they don’t C#."; break;
        case 15: str = "A programmer is heading out to the grocery store, so his wife tells him “get a gallon of milk, and if they have eggs, get a dozen.” He returns with 13 gallons of milk."; break;
        case 16: str = "Programmer: An organism that turns coffee into software."; break;
        case 17: str = "Q: What is the difference between a programmer and a non-programmer? A: The non-programmer thinks a kilobyte is 1000 bytes while a programmer is convinced that a kilometer is 1024 meters."; break;
        case 18: str = "Q: What’s the best thing thing about UDP jokes? A: I don’t care if you get them."; break;
        case 19: str = "Q: Why do programmers always mix up Halloween and Christmas? A: Because Oct 31 equals Dec 25."; break;
        case 20: str = "Programmer: A person who fixed a program you didn’t know you had in a way that you don’t understand."; break;
        case 21: str = "My attitude isn’t bad, it’s in beta."; break;
        case 22: str = "What do cats and programmers have in common? When either one is unusually happy and excited, it’s because they found a bug."; break;
        case 23: str = "[“hip”,”hip”]     (hip hip array!)"; break;
        case 24: str = "The more I C, the less I see"; break;
        case 25: str = "What do you call a programmer who vomits at IHOP? A stack overflow."; break;
        case 26: str = "Computers will never fully replace humans until they learn to laugh at the boss’s jokes"; break;
        case 27: str = "while (alive) { eat(); sleep (); code ();}"; break;
        case 28: str = "There are 2 types of people in the world. Those who can extrapolate from incomplete data…"; break;
        case 29: str = "What do you call a programmer who vomits at IHOP? A stack overflow."; break;
        case 30: str = "; The Ultimate Hide and Seek Champion."; break;
        case 31: str = "99 little bugs in the code, 99 little bugs, you take one down and patch it around, 125 little bugs in the code."; break;
        case 32: str = "I’ve got a really good UDP joke to tell you, but I don’t know if you’ll get it."; break;
        case 33: str = "There are 10 kinds of people in the world. Those who understand binary and those who don’t."; break;
        case 34: str = "A guy walks into a bar and asks for 1.4 root beers. The bartender says “I’ll have to charge you extra, that’s a root beer float”. The guy says “In that case, better make it a double."; break;
        case 35: str = "Programming is 10% writing code and 90% understanding why it’s not working."; break;
        case 36: str = "Sometimes it pays to stay in bed on Monday, rather than spending the rest of the week debugging Monday’s code."; break;
        case 37: str = "The generation of random numbers is too important to be left to chance."; break;
        case 38: str = "What do you call a programmer from Finland? Nerdic."; break;
        case 39: str = "When there’s code, there’s bug."; break;
        case 40: str = "If its working, don’t touch it."; break;
        case 41: str = "Bad code can’t be debugged. Neither can good code."; break;
        case 42: str = "If you don’t know something, Google it."; break;
        case 43: str = "A programmer’s day: Coding Rules."; break;
        case 44: str = "There’s no place like 127.0.0.1"; break;
        case 45: str = "Why do programmers take so long in the shower? They read the directions on the shampoo bottle and follow them to the letter: Lather, rinse, and repeat."; break;
        case 46: str = "A computer programmer rushes his wife to the hospital where she gives birth to their child. The doctor first hands the baby to the programmer. “Well?” his wife says impatiently. “Is it a boy, or is it a girl?” Smiling, the programmer replies, “Yes.”"; break;
        case 47: str = "If at first you don’t succeed, call it version 1.0"; break;
        case 48: str = "My love for you has no bugs."; break;
        case 49: str = "What is the most used language in programming? Profanity."; break;
        case 50: str = "Real programmers count from 0."; break;
        case 51: str = "My mind is like an internet browser, 19 tabs open, 3 of them are frozen, ads popping up everywhere, I have no idea where the music is coming from."; break;
        case 52: str = "Physics is the universe’s operating system."; break;
        case 53: str = "Q: Why can’t you trust an atom? A: They make up everything."; break;
        case 54: str = "Einstein developed a theory about space. And it was about time, too!"; break;
        case 55: str = "Math is either extremely frustrating or extremely satisfying, there is no in between."; break;
        case 56: str = "Two bytes meet. The first byte asks, 'Are you ill?' The second byte replies, 'No, just feeling a bit off.'"; break;
        case 57: str = "Eight bytes walk into a bar. The bartender asks, 'Can I get you anything?' 'Yeah,' reply the bytes. 'Make us a double.'"; break;
        case 58: str = "Q. How did the programmer die in the shower? A. He read the shampoo bottle instructions: Lather. Rinse. Repeat."; break;
        case 59: str = "How many programmers does it take to change a light bulb? None – It’s a hardware problem."; break;
        case 60: str = "Why do programmers always mix up Halloween and Christmas? Because Oct 31 equals Dec 25."; break;
        case 61: str = "There are only 10 kinds of people in this world: those who know binary and those who don’t."; break;
        case 62: str = "A programmer walks to the butcher shop and buys a kilo of meat. An hour later he comes back upset that the butcher shortchanged him by 24 grams."; break;
        case 63: str = "Programming is 10% science, 20% ingenuity, and 70% getting the ingenuity to work with the science."; break;
        case 64: str = "Programming is like sex: One mistake and you have to support it for the rest of your life."; break;
        case 65: str = "A man is smoking a cigarette and blowing smoke rings into the air. His girlfriend becomes irritated with the smoke and says, 'Can’t you see the warning on the cigarette pack? Smoking is hazardous to your health!' To which the man replies, 'I am a programmer. We don’t worry about warnings; we only worry about errors.'"; break;
        case 66: str = "There are three kinds of lies: Lies, damned lies, and benchmarks."; break;
        case 67: str = "A programmer is walking along a beach and finds a lamp. He rubs the lamp, and a genie appears. 'I am the most powerful genie in the world. I can grant you any wish, but only one wish.'"; break;
        case 68: str = "A programmer had a problem once. He decided to use Java. Now he has a Problem Factory."; break;
        case 69: str = "Programmer fixes 10 of the bugs and explains to the testing department that the other 10 aren’t really bugs. Testing department finds that five of the fixes didn’t work and discovers 15 new bugs."; break;
        case 70: str = "Due to marketing pressure and an extremely premature product announcement based on overly-optimistic programming schedule, the product is released. Original programmer, having cashed his royalty check, is nowhere to be found."; break;
        case 71: str = "Newly-assembled programming team fixes almost all of the 137 bugs, but introduce 456 new ones."; break;
        case 72: str = "Original programmer sends underpaid testing department a postcard from Fiji. Entire testing department quits."; break;
        case 73: str = "Company is bought in a hostile takeover by competitor using profits from their latest release, which had 783 bugs."; break;
        case 74: str = "New CEO is brought in by board of directors. He hires a programmer to redo program from scratch."; break;
        case 75: str = "By filing this bug report you have challenged the honor of my family. Prepare to die!"; break;
        case 76: str = "You question the worthiness of my code? I should kill you where you stand!"; break;
        case 77: str = "This machine is GAGH! I need dual Pentium processors if I am to do battle with this code!"; break;
        case 78: str = "Our users will know fear and cower before our software! Ship it! Ship it and let them flee like the dogs they are!"; break;
        case 79: str = "Behold, the keyboard of Kalis! The greatest Klingon code warrior that ever lived!"; break;
        case 80: str = "The programmer compiled an array of reasons as to why he can’t find a girlfriend with a good <HEAD> on her <BODY>, reason 0 being that he has limited cache. So he searches his memory to recall connecting to the TCP/IP tunnel of his last girlfriend — sometimes even without a secure socket. His last girlfriend always complained about his lack of comments. He fumed, 'I hate commenting!' Realizing it was a program requirement, he told her she had nice bits. This resulted in a Syntax Error. Now she demanded a massage, but this was rejected as 'Feature Creep.' He smacked her back-end and shouted, 'Who’s your parent node?!' He scanned for open ports. He attempted to install a backdoor worm but her response was 403. While his data uploaded into her input device, she considered terminating the process. But instead she initiated a Do While loop where she recalled a previous boyfriend with a larger pointer. To expedite the routine routine, she screamed, 'Hack into my system! Hack deep into my system! You’re 1337, baby!' This caused his stack to overflow, and he shot his GUI on her interface."; break;
        case 81: str = "A SQL statement walks into a bar. It sees two tables and says 'Hey, can I join you guys?'"; break;

	}
	addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), str));
}

/*
    Prototype for the command => `/msg raultbot: random`
*/
static void	botRandom(Server *server, int const client_fd, Client &client, std::string &bot)
{
	int index = rand() % 10 + 1;
	
	std::string str;
	switch (index)
	{
		case 1: str = "Wearing headphones for just an hour could increase the bacteria in your ear by 700 times."; break;
		case 2: str = "Google images was literally created after Jennifer Lopez wore that infamous dress at the 2000 Grammys"; break;
		case 3: str = "Los Angeles' full name is 'El Pueblo de Nuestra Senora la Reina de los Angeles de Porciuncula'"; break;
		case 4: str = "Tigers have striped skin, not just striped fur."; break;
		case 5: str = "Like fingerprints, everyone's tongue print is different."; break;
		case 6: str = "Cat urine glows under a black-light."; break;
		case 7: str = "A shrimp's heart is in its head."; break;
		case 8: str = "The Spice Girls were originally a band called Touch."; break;
		case 9: str = "The unicorn is the national animal of Scotland"; break;
		case 10: str = "In 2014, there was a Tinder match in Antarctica"; break;
	}
	addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), str));
}

std::string doubleToString(double nb)
{
    std::ostringstream oss;
    oss << nb;
    return oss.str();
}

void	bot(Server *server, int const client_fd, Client &client, std::string bot_cmd){
	std::string bot = BOT_NAME;
	std::string	validCmds[4] = {
		":HELP",
		":RANDOM",
		":QUIZZ",
		":JOKE",
		};

    if (client.bot_question.firstTime == false)
    {
        FirstAnswer(server, client_fd, client);
    }
	for (size_t i = 0; i < bot_cmd.size(); i++)
		bot_cmd[i] = std::toupper(bot_cmd[i]);
    if (client.bot_question.questionType != None)
    {
        if (searchString(bot_cmd.c_str(), ToUpper(client.bot_question.answer).c_str())
            || (bot_cmd == ":1"
                && ((client.bot_question.questionType == LargerArea || client.bot_question.questionType == MostPopulated)
                    && client.bot_question.answer == client.bot_question.country1))
            || (bot_cmd == ":2"
                && ((client.bot_question.questionType == LargerArea || client.bot_question.questionType == MostPopulated)
                    && client.bot_question.answer == client.bot_question.country2)))
        {
            addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), GREEN + "Good answer!" + RESET));
        }
        else
        {
            addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), RED + "Wrong!" + RESET));
            addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), "The right answer is " + GREEN + client.bot_question.answer + RESET + "."));
        }
        switch (client.bot_question.questionType)
        {
            case LargerArea:
                addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), "The area of " + TEAL + client.bot_question.country1 + RESET + " is " + TEAL + formatNumber(client.bot_question.area1) + RESET + " Km²."));
                addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), "The area of " + TEAL + client.bot_question.country2 + RESET + " is " + TEAL + formatNumber(client.bot_question.area2) + RESET + " Km²."));
            break;
            case MostPopulated:
                addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), TEAL + client.bot_question.country1 + RESET + " has " + TEAL + formatNumber(client.bot_question.pop1) + RESET + " inhabitants."));
                addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), TEAL + client.bot_question.country2 + RESET + " has " + TEAL + formatNumber(client.bot_question.pop2) + RESET + " inhabitants."));
            break;
            default:
            break;
        }
        client.bot_question.questionType = None;
        return;
    }
	int index = 0;
	while (index < 4)
	{
		if (searchString(bot_cmd.c_str(), validCmds[index].c_str()))
			break;
		index++;
	}
	switch (index + 1)
	{
		case 1: addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), "Ask me 'RANDOM', 'JOKE' or 'QUIZZ': You can ask questions about the Leader, the Capital, the Size and the Population of any Country")); break;
		case 2: botRandom(server, client_fd, client, bot); break;
		case 3: botQuizz(server, client_fd, client, bot_cmd); break;
		case 4: botJoke(server, client_fd, client, bot); break;
		default:
			addToClientBuffer(server, client_fd, RPL_PRIVMSG(bot, bot, client.getNickname(), "Invalid request, ask 'HELP' for more infos"));
	}
}