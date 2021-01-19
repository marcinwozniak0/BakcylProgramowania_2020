#include <iostream>
#include <fstream>

#include "Logger.hpp"

using namespace std;


int main()
{
   Logger logger;
   logger.log("test");
   logger.log("??"); 

   return 0;
}
