#pragma once

#ifndef EXPRESSION_EVALUATION 

#define EXPRESSION_EVALUATION

#include<stack>
#include<string>
#include<ctype.h>

bool isoperate(char ch);
bool is_part_of_number(char ch);
int get_priority_of_operate(char op);
std::string infix_to_postfix(std::string& infix);
void deal_with_operate(char ch, std::stack<char>& stk, std::string& postfix);
double expression_to_evaluation(std::string& infix);

#endif // !EXPRESSION_EVALUATION 
