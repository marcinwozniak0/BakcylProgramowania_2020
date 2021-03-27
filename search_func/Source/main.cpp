#include <iostream>
#include <sqlite3.h>
#include "search_func.hpp"

int main()
{
	std::string str = std::to_string(static_cast<std::size_t> (11));
	std::cout << "ok " << str << std::endl;
	return 0;
}
