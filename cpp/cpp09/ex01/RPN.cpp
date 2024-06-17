#include "RPN.hpp"

RPN::RPN(){};

RPN::RPN(const RPN &other)
{
	(void)other;
};

RPN::~RPN(){};

RPN &RPN::operator=(const RPN &other)
{
	(void)other;
	return *this;
};

static bool is_expression_valid(std::string expression)
{
	bool last_was_space = true;
	if (expression.empty())
		return false;
	for (size_t i = 0; i < expression.length(); i++)
	{
		if (expression[i] != '+' && expression[i] != '-' && expression[i] != '*' && expression[i] != '/' && !std::isdigit(expression[i]) && expression[i] != ' ')
			return false;
		if (expression[i] == ' ')
		{
			if (last_was_space)
				return false;
			if (i == expression.length() - 1)
				return false;
			last_was_space = true;
		}
		else
		{
			if (!last_was_space)
				return false;

			last_was_space = false;
		}
	}

	return true;
};

long long RPN::solve_expression(std::string expression)
{
	if (!is_expression_valid(expression))
		throw std::runtime_error("Invalid expression");
	std::stack<long long> stack;

	size_t i = 0;
	while (i < expression.length())
	{
		if (expression[i] == ' ')
		{
			i++;
			continue;
		}
		if (std::isdigit(expression[i]))
		{
			stack.push(std::stoll(&expression[i]));
			i++;
		}
		else
		{
			if (stack.size() < 2)
				throw std::runtime_error("Invalid expression, operator on less than 2 numbers");
			long long a = stack.top();
			stack.pop();
			long long b = stack.top();
			stack.pop();
			if (expression[i] == '+')
				stack.push(b + a);
			else if (expression[i] == '-')
				stack.push(b - a);
			else if (expression[i] == '*')
				stack.push(b * a);
			else if (expression[i] == '/')
			{
				if (a == 0)
					throw std::runtime_error("Division by zero (impossible)");
				stack.push(b / a);
			}
			i++;
		}
	}
	return stack.top();
};