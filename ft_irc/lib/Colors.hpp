#ifndef COLORS_HPP
# define COLORS_HPP

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdarg>
#include <sstream>

// Black background with red font color
#define ERRCOLOR RGB2(Colors::Red(), Colors::Black())

// Custom colors
#define LIGHTRED		"\033[38;2;255;100;100m"
#define LIME			"\033[38;2;165;255;0m"
#define DARKTEAL		"\033[38;2;0;100;100m"
#define TEAL			"\033[38;2;0;180;180m"
#define LIGHTTEAL		"\033[38;2;0;215;215m"
#define ROSERED			"\033[38;2;255;0;93m"
#define GOLD			"\033[38;2;204;146;50m"
#define ORANGE			"\033[38;2;255;145;0m"
#define BROWN			"\033[38;2;60;28;0m"
#define CORAL			"\033[38;2;255;127;80m"
#define GREY			"\033[38;2;100;100;100m"
#define ERRED			"\033[38;2;255;0;0m"

// Text Styles
#define RESET			"\033[0m"
#define BOLD			"\033[1m"
#define DIM				"\033[2m"
#define ITALIC			"\033[3m"
#define UNDERLINE		"\033[4m"
#define BLINK_SLOW		"\033[5m"
#define BLINK_RAPID		"\033[6m"
#define REVERSE_VIDEO	"\033[7m"
#define CONCEALED		"\033[8m"
#define CROSSED_OUT		"\033[9m"

// Text Colors
#define BLACK			"\033[0;30m"
#define RED				"\033[0;31m"
#define GREEN			"\033[0;32m"
#define YELLOW			"\033[0;33m"
#define BLUE			"\033[0;34m"
#define MAGENTA			"\033[0;35m"
#define CYAN			"\033[0;36m"
#define WHITE			"\033[0;37m"

// Background Colors
#define BG_BLACK		"\033[40m"
#define BG_RED			"\033[41m"
#define BG_GREEN		"\033[42m"
#define BG_YELLOW		"\033[43m"
#define BG_BLUE			"\033[44m"
#define BG_MAGENTA		"\033[45m"
#define BG_CYAN			"\033[46m"
#define BG_WHITE		"\033[47m"

struct Color
{
	int r, g, b;
};

class Colors
{
	public:
		static Color& Black() {
			static Color blackColor = {0, 0, 0}; // Black color
			return blackColor;
		}
		static Color& Blue() {
			static Color blueColor = {0, 0, 255}; // Blue color
			return blueColor;
		}
		static Color& Brown() {
			static Color brownColor = {60, 28, 0}; // Brown color
			return brownColor;
		}
		static Color& Cyan() {
			static Color cyanColor = {0, 255, 255}; // Cyan color
			return cyanColor;
		}
		static Color& DarkBrown() {
			static Color darkBrownColor = {43, 0, 0}; // Dark Brown color
			return darkBrownColor;
		}
		static Color& DarkMagenta() {
			static Color darkMagentaColor = {139, 0, 139}; // Dark Magenta color
			return darkMagentaColor;
		}
		static Color& DeepPink() {
			static Color deepPinkColor = {255, 20, 147}; // Deep Pink color
			return deepPinkColor;
		}
		static Color& Green() {
			static Color greenColor = {0, 255, 0}; // Green color
			return greenColor;
		}
		static Color& Magenta() {
			static Color magentaColor = {255, 0, 255}; // Magenta color
			return magentaColor;
		}
		static Color& MistyRose() {
			static Color mistyRoseColor = {255, 228, 225}; // Misty Rose color
			return mistyRoseColor;
		}
		static Color& NightBlue() {
			static Color nightBlueColor = {25, 25, 112}; // Night Blue color
			return nightBlueColor;
		}
		static Color& Orange() {
			static Color orangeColor = {255, 145, 0}; // Orange color
			return orangeColor;
		}
		static Color& Pink() {
			static Color pinkColor = {255, 192, 203}; // Pink color
			return pinkColor;
		}
		static Color& Red() {
			static Color redColor = {255, 0, 0}; // Red color
			return redColor;
		}
		static Color& RoyalBlue() {
			static Color royalBlueColor = {65, 105, 225}; // Royal Blue color
			return royalBlueColor;
		}
		static Color& Violet() {
			static Color violetColor = {255, 0, 255}; // Violet color
			return violetColor;
		}
		static Color& White() {
			static Color whiteColor = {255, 255, 255}; // White color
			return whiteColor;
		}
		static Color& Yellow() {
			static Color yellowColor = {255, 255, 0}; // Yellow color
			return yellowColor;
		}
		static Color& Gold() {
			static Color goldColor = {204, 146, 50}; // Gold color
			return goldColor;
		}
		static Color& Teal() {
			static Color tealColor = {0, 180, 180}; // Teal color
			return tealColor;
		}
		static Color& DarkTeal() {
			static Color darkTealColor = {0, 100, 100}; // Dark Teal color
			return darkTealColor;
		}
		static Color& LightTeal() {
			static Color lightTealColor = {0, 215, 215}; // Light Teal color
			return lightTealColor;
		}
		static Color& Coral() {
			static Color coralColor = {255, 127, 80}; // Coral color
			return coralColor;
		}
};

typedef enum color_mode
{
	foreground = 38,
	background = 48
}				Mode;

/* Keeps the R, G, B values between 0 and 255. */
inline int	SetMinMax(int value)
{
	if (value < 0)
		value = 0;
	else if (value > 255)
		value = 255;
	return (value);
}

/*
	To cast an int/double/float or anything that is compatible into a `std::string`
*/
template <typename T>
std::string to_str(const T& value)
{
    std::ostringstream os;
    os << value;
    return os.str();
}

/* Returns the complete color code with the given parameters. 
	@param r(red) 0 - 255.
	@param g(green) 0 - 255.
	@param b(blue) 0 - 255.
	@param mode (optional) To change the foreground(character) or the background color.
*/
inline std::string RGB(int r, int g, int b, Mode mode = foreground)
{
	std::stringstream ss;
	ss << "\033[" << mode << ";2;" << r << ";" << g << ";" << b << "m";
	return (ss.str());
}

/* Returns the complete color code with the given parameters. 
	@param color The color to apply.
	@param mode (optional) To change the foreground(character) or the background color.
*/
inline std::string RGB(const Color &color, Mode mode)
{
	std::stringstream ss;
	ss << "\033[" << mode << ";2;" << color.r << ";" << color.g << ";" << color.b << "m";
	return (ss.str());
}

/* Returns the complete foreground and background color code with the given parameters. 
	@param r(foreground red) 0 - 255.
	@param g(foreground green) 0 - 255.
	@param b(foreground blue) 0 - 255.
	@param bg_r(background red) 0 - 255.
	@param bg_g(background green) 0 - 255.
	@param bg_b(background blue) 0 - 255.
*/
inline std::string RGB2(int r, int g, int b, int bg_r, int bg_g, int bg_b)
{
	std::stringstream ss;
	ss << "\033[38;2;" << r << ";" << g << ";" << b << ";48;2;"
		<< bg_r << ";" << bg_g << ";" << bg_b << "m";
	return (ss.str());
}

inline std::string RGB2(const Color &fg_color, const Color &bg_color)
{
	std::stringstream ss;
	ss << "\033[38;2;" << fg_color.r << ";" << fg_color.g << ";" << fg_color.b
	<< ";48;2;" << bg_color.r << ";" << bg_color.g << ";" << bg_color.b << "m";
	return (ss.str());
}

/*
	Returns an error message containing the text in red in a black background.
	@param msg The message to display.
	@param foregroundOnly If true, prints the message in a vibrant red color. If false (by default), prints the message with a black background and a vibrent red color
*/
inline std::string	ErrMsg(std::string msg, bool foregroundOnly = false)
{
	std::string color_mode = foregroundOnly ? ERRED : ERRCOLOR;
	std::cerr << std::endl << color_mode << "Error:" << std::endl <<
		std::setw(8) << "" << msg << RESET << std::endl;
	return ("");
}

static inline std::string ApplyColor(Color &toColor, Color &fromColor, size_t &i, size_t length, std::string &str, double div, Mode mode)
{
	double		r_off, g_off, b_off;
	Color		color;
	std::stringstream ss;

	r_off = (toColor.r - fromColor.r) / div;
	g_off = (toColor.g - fromColor.g) / div;
	b_off = (toColor.b - fromColor.b) / div;
	for (size_t j = 0; j < div; j++)
	{
		if (i == length)
			break ;
		color.r = fromColor.r + r_off * (j + 1);
		color.g = fromColor.g + g_off * (j + 1);
		color.b = fromColor.b + b_off * (j + 1);
		ss << "\033[" << mode << ";2;"
			<< SetMinMax(color.r) << ";"
			<< SetMinMax(color.g) << ";"
			<< SetMinMax(color.b) << "m" << str[i] << "\033[0m";
		i++;
	}
	fromColor = toColor;
	return ss.str();	
}

/* Returns a string with a single color.
	@param arg The string/int/anything to be printed.
	@param mode To change the foreground(character) or the background color.
	@param color The color to be applied.
*/
template <typename T>
std::string		ToColor(T arg, Mode mode, const Color &color)
{
	std::string str = to_str(arg);
	std::stringstream ss;
	ss << "\033[" << mode << ";2;"
			<< SetMinMax(color.r) << ";"
			<< SetMinMax(color.g) << ";"
			<< SetMinMax(color.b) << "m" << str << "\033[0m";
	return ss.str();
}

/* Returns a string with a single color.
	@param arg The string/int/anything to be printed.
	@param color The color to be applied.
*/
template <typename T>
std::string		ToColor(T arg, const Color &color)
{
	return ToColor(arg, foreground, color);
}

/* Returns a string with color gradients between each color.
	@param arg The string/int/anything to be printed.
	@param mode To change the foreground(character) or the background color.
	@param count The amount of colors to be calculated.
	@param ... The colors (ex: `Colors::Red`).
*/
template <typename T>
std::string		ToColor(T arg, Mode mode, size_t count, ...)
{
	std::string str = to_str(arg);
	std::stringstream ss;
	va_list		va;
	Color		fromColor, toColor;
	size_t		length = str.length();
	double		div = (double)length / (count - 1);
	size_t		i = 0;

	if (count <= 1)
		return (ErrMsg("You must put at least 2 colors!"));
	if (length < count)
		return (ErrMsg("You must put less colors than the total character count!"));
	va_start(va, count);
	fromColor = va_arg(va, Color);
	while (i < length)
	{
		toColor = va_arg(va, Color);
		ss << ApplyColor(toColor, fromColor, i, length, str, div, mode);
	}
	va_end(va);
	return (ss.str());
}

/* Returns a string with color gradients between each color.
	@param arg The string/int/anything to be printed.
	@param count The amount of colors to be calculated.
	@param ... The colors (ex: `Colors::Red`).
*/
template <typename T>
std::string		ToColor(T arg, size_t count, ...)
{
	std::string str = to_str(arg);
	std::stringstream ss;
	va_list		va;
	Color		fromColor, toColor;
	size_t		length = str.length();
	double		div = (double)length / (count - 1);
	size_t			i = 0;

	if (count <= 1)
		return (ErrMsg("You must put at least 2 colors!"));
	if (length < count)
		return (ErrMsg("You must put less colors than the total character count!"));
	va_start(va, count);
	fromColor = va_arg(va, Color);
	while (i < length)
	{
		toColor = va_arg(va, Color);
		ss << ApplyColor(toColor, fromColor, i, length, str, div, foreground);
	}
	va_end(va);
	return (ss.str());
}

/* Returns a string with color gradients between both colors.
	@param arg The string/int/anything to be printed.
	@param mode To change the foreground(character) or the background color.
	@param start The starting color.
	@param end The final color.
*/
template <typename T>
std::string		ToColor(T arg, Mode mode, const Color &start, const Color &end)
{
	return (ToColor(arg, mode, 2, start, end));
}

/* Returns a string with color gradients between both colors.
	@param arg The string/int/anything to be printed.
	@param start The starting color.
	@param end The final color.
*/
template <typename T>
std::string		ToColor(T arg, const Color &start, const Color &end)
{
	return (ToColor(arg, 2, start, end));
}

/* Returns a string with beautiful rainbow colors! 
	@param arg The string/int/anything to be printed.
	@param mode (optional) To change the foreground(character) or the background color.
*/
template <typename T>
std::string Rainbow(T arg, Mode mode = foreground)
{
	return (ToColor(arg, mode, 7, Colors::Red(), Colors::Yellow(), Colors::Green(), Colors::Cyan(), Colors::Blue(), Colors::Violet(), Colors::Red()));
}
#endif