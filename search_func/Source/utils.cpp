#include "utils.hpp"


int find(std::vector<std::string> vector, std::string value)
{
    int i;
	for(i = 0; i < (int)vector.size(); ++i)
	{
		if(vector[i] == value)
		{
			break;
		}
	}
	if(i > (int)vector.size()) return -1;
	return i;
}


std::string toString(std::size_t x)
{
	std::string s = "";
	while(x > 0)
	{
		s = (char)(x % 10 + '0') + s;
		x /= 10;
	}
	return s;
}

