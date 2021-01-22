#include <iostream>
#include <fstream>
#include "Logger.hpp"
#include "ExceptionLevels.cpp"

void printLogLevel(const int level)
{

    if(level == ExceptionLevel(fine))
    {
    	std::cout << "FINE: "; 
    }
    else if(level == ExceptionLevel(warning))
    {
    	std::cout << "WARNING: "; 
    }	
    else if(level == ExceptionLevel(error))
    {
    	std::cout << "ERROR: "; 
    }
    else if(level == ExceptionLevel(fatal))
    {
    	std::cout << "FATAL ERROR: "; 
    }

}

void Logger::log(const std::string& message, const int level)
{
    if (logs.is_open())
    {     
    
        logs << message << "\n";
    }
    else
    {
        std::ofstream outfile("logs.txt");

        logs.open("logs.txt", std::ios::app);
        
        logs << message << "\n";
    }
    
    printLogLevel(level);
	
    std::cout << message << std::endl;
    
}

Logger::~Logger() {
logs.close();
}

