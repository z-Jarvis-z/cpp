#pragma once

#ifndef K_M_P

#define K_M_P

#include<vector>
#include<string>
std::vector<unsigned int> generate_next(std::string& pattern);
std::vector<unsigned int> generate_next_val(std::string& pattern);
unsigned int k_m_p(std::string& str, std::string& pattern);

#endif // K_M_P