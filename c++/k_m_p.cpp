#include"k_m_p.h"

std::vector<unsigned int> generate_next(std::string& pattern)
{
	std::vector<unsigned int> next{0};
	next.reserve(pattern.size());
	unsigned int prefix_len = 0;
	unsigned int i = 1;
	while (i < pattern.size())
	{
		if (pattern[prefix_len] == pattern[i])
		{
			prefix_len += 1;
			next.push_back(prefix_len);
			i++;
		}
		else
		{
			if (prefix_len == 0)
			{
				next.push_back(prefix_len);
				i++;
			}
			else
			{
				prefix_len = next[prefix_len - 1];
			}
		}

	}
	return next;
}

std::vector<unsigned int> generate_next_val(std::string& pattern) 
{
	std::vector<unsigned int> next_val = generate_next(pattern);
	unsigned int i = 2;
	if (pattern[1] == pattern[0])
		next_val[1] = 0;
	while (i < pattern.size())
	{
		if (pattern[i] == pattern[next_val[i - 1]])
			if(next_val[i-1])
				next_val[i - 1] = next_val[next_val[i - 1]-1];
		i++;
	}
	return next_val;
}

unsigned int k_m_p(std::string& str, std::string& pattern)
{
	std::vector<unsigned int> next = generate_next_val(pattern);
	unsigned int i = 0;
	unsigned int j = 0;
	while (i < str.size())
	{
		if (str[i] == pattern[j])
		{
			if (j == pattern.size()-1)
				return i - j;
			i++;
			j++;
		}
		else
		{
			if (j == 0)
			{
				i++;
			}
			else
			{
				j = next[j - 1];
			}
		}
	}
	return -1;
}