#pragma once

#ifndef TOOL_KIT

#define TOOL_KIT

#include<string>
#include<vector>

std::string& trim_(std::string& str);
std::vector<std::string> split_ch(std::string str, const char ch = ' ');

#endif // TOOL_KIT
