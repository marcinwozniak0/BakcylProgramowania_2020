#include <iostream>

struct Logger
{
   std::fstream logs;
   void log(const std::string& message, const int exc);
   ~Logger();
};

