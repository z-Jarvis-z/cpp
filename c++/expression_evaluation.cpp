#include"expression_evaluation.h"
#include"tool_kit\tool_kit_string.h"

int get_priority_of_operate(char op)
{
	switch (op) {
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	default:
		return 0;
	}
}
bool isoperate(char ch)
{
	switch (ch) {
	case '+':
	case '-':
	case '*':
	case '/':
	case '(':
	case ')':
	case '=':
		return true;
	default:
		return false;
	}
}
bool is_part_of_number(char ch)
{
	if (isdigit(ch) || ch == '.')
		return true;
	return false;
}
void deal_with_operate(char ch, std::stack<char>& stk, std::string& postfix)
{
	if (stk.empty() || ch == '(')
	{
		stk.push(ch);
		return;
	}
	if (ch == ')')
	{
		while (stk.top() != '(')
		{
			postfix += stk.top();
			stk.pop();
			postfix += ' ';
		}
		stk.pop();
		return;
	}
	while(get_priority_of_operate(ch) <= get_priority_of_operate(stk.top()))
	{
		postfix += stk.top();
		stk.pop();
		postfix += ' ';
		if (stk.empty())
			break;
	}	
	stk.push(ch);
}
std::string infix_to_postfix(std::string& infix)
{
	std::stack<char> stk;
	std::string postfix;

	for (unsigned int i = 0; i < infix.size(); ++i)
	{
		char ch = infix[i];
		if (ch == ' ')
			continue;
		if (isoperate(ch))
		{
			deal_with_operate(ch, stk, postfix);
			continue;
		}
		while(is_part_of_number(ch))
		{
			postfix += ch;
			if (is_part_of_number(infix[i + 1]))
				ch = infix[++i];
			else
			{
				postfix += ' ';
				break;
			}
		}
	}

	while (!stk.empty())
	{
		postfix += stk.top();
		stk.pop();
	}
	return postfix;
}
double expression_to_evaluation(std::string& infix)
{
	std::vector<std::string> vec;
	vec = split_ch(infix_to_postfix(infix));
	std::stack<double> stk;
	for (auto& str : vec)
	{
		if (is_part_of_number(str[0]))
		{
			stk.push(std::stod(str));
			continue;
		}
		if (str == "=")
			return stk.top();

		double a = stk.top();
		stk.pop();

		if(str == "+")
			stk.top() += a;
		if (str == "-")
			stk.top() -= a;
		if (str == "*")
			stk.top() *= a;
		if (str == "/")
			stk.top() /= a;
	}
	return stk.top();
}