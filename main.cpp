#include <iostream>
#include <fstream>

#include "Logger.hpp"


int main()
{
   Logger logger;
   logger.log("test");
   logger.log("??"); 

   return 0;
}
