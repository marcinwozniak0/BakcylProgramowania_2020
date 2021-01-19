#include <iostream>
#include <fstream>

#include "logger.hpp"

using namespace std;


int main()
{
   Logger logger;
   logger.log("test");
   logger.log("??"); 

   return 0;
}
