#include <string>
#include <stack>

#include <iostream>
#include <limits>
#include <sstream>

class RPN
{
private:
	RPN();
	RPN(const RPN &other);
	~RPN();

	RPN &operator=(const RPN &other);

public:
	static long long solve_expression(std::string expression);
};