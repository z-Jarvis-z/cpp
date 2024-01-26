#include<iostream>
#include"k_m_p.h"

static void test()
{
	std::string str = "ababgooglebaababaabc";
	std::string pattern = "google";
	std::vector<unsigned int> next = generate_next_val(pattern);
	for (auto& value : next)
	{
		std::cout << value<<std::endl;
	}
	std::cout << k_m_p(str, pattern) << std::endl;
}
