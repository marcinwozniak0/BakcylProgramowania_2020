#include <iostream>
#include <fstream>

#include "Logger.hpp"

void Logger::log(std::string msg)
{
    std::fstream logs;

    if (logs.good())
    {
        logs.open("logs.txt", std::ios::app);
        
        logs << msg << "\n";

        logs.close();
    }
    else
    {
        std::ofstream outfile("logs.txt");

        logs.open("logs.txt", std::ios::app);
        
        logs << msg << "\n";

        logs.close();
    }
    

    std::cout << msg << std::endl;
} 

