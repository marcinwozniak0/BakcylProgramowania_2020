#include <iostream>

struct Logger
{
    std::fstream logs;
   void log(std::string msg);
   
   ~Logger() {
   logs.close();
   };
   
};

