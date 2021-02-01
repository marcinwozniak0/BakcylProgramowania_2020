#include <iostream>
#include <fstream>
#include <cstdio>
#include <ctime>
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
const std::string currentDateTime() 
{
    time_t now = time(0);
    struct tm  tstruct;
    char currentTime[80];
    tstruct = *localtime(&now);
    strftime(currentTime, sizeof(currentTime), "[%Y-%m-%d %X]", &tstruct);

    return currentTime;
}

void Logger::log(const std::string& msg, const int exc)
{
    if (logs.is_open())
    {     
        logs << currentDateTime() << " " << msg << "\n\n";
    }
    else
    {
        std::ofstream outfile("logs.txt");

        logs.open("logs.txt", std::ios::app);
        
        logs << currentDateTime() << " " << msg << "\n\n";
    }
    
    printLogLevel(level);
	
    std::cout << message << std::endl;
    
}

Logger::~Logger() {
logs.close();
}
