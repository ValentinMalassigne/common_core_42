#include <string>
#include <stack>

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