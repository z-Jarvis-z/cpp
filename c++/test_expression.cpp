#include"expression_evaluation.h"
#include<iostream>
static void test()
{
	std::string s= "1+2/3-4+5*2-(3+1)=";
	double a = expression_to_evaluation(s);
	std::cout<<a<<std::endl;
}
int main()
{
	test();
	return 0;
}