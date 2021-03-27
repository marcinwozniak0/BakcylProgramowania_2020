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

