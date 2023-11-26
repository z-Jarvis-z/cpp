#include"tool_kit_string.h"

std::string& trim_(std::string& str)
{
	const char* space = "\r\n\t";
	str.erase(str.find_last_not_of(space));
	str.erase(str.find_first_not_of(space));
	return str;
}
std::vector<std::string> split_ch(std::string str, const char ch)
{
	std::vector<std::string> vec{};
	auto n = str.find(ch);
	while (n != std::string::npos)
	{
		vec.emplace_back(str.substr(0, n));
		str.erase(0, n + 1);
		n = str.find(ch);
	}
	return vec;
}