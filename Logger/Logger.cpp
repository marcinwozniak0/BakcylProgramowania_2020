#include <iostream>
#include <fstream>
#include "Logger.hpp"
#include "ExceptionLevels.cpp"

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
    
    if(level == ExceptionLevel(fine))
    {
    	std::cout <<"FINE: "; 
	}
    if(level == ExceptionLevel(warning))
    {
    	std::cout <<"WARNING: "; 
	}	
    if(level == ExceptionLevel(error))
    {
    	std::cout <<"ERROR: "; 
	}
    if(level == ExceptionLevel(fatal))
    {
    	std::cout <<"FATAL ERROR: "; 
	}
	
    std::cout << message << std::endl;
    
}

Logger::~Logger() {
logs.close();
}

