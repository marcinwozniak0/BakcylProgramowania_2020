#include <iostream>
#include <fstream>

#include "Logger.hpp"

void Logger::log(std::string msg)
{
    if (logs.good())
    {
        logs.open("logs.txt", std::ios::app);
        
        logs << msg << "\n";
    }
    else
    {
        std::ofstream outfile("logs.txt");

        logs.open("logs.txt", std::ios::app);
        
        logs << msg << "\n";
    }
    

    std::cout << msg << std::endl;
}

