#include <iostream>
#include <fstream>
#include <cstdio>
#include <ctime>
#include "Logger.hpp"
#include "ExceptionLevels.cpp"


std::string logLevel(const int level)
{
    std::string exception;
    
    if(level == ExceptionLevel(fine))
    {
    	exception = "FINE: "; 
    }
    else if(level == ExceptionLevel(warning))
    {
    	exception = "WARNING: "; 
    }	
    else if(level == ExceptionLevel(error))
    {
    	exception = "ERROR: "; 
    }
    else if(level == ExceptionLevel(fatal))
    {
    	exception = "FATAL ERROR: "; 
    }

    return exception;
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

void Logger::log(const std::string& message, const int exc)
{
    if (logs.is_open())
    {     
        logs << currentDateTime() << " " << logLevel(exc) << " " << message << "\n\n";
    }
    else
    {
        std::ofstream outfile("logs.txt");

        logs.open("logs.txt", std::ios::app);
        
        logs << currentDateTime() << " " << logLevel(exc) << " " << message << "\n\n";
    }
    
    std::cout << currentDateTime() << " " << logLevel(exc) << " " << message << "\n\n";
}

Logger::~Logger() {
logs.close();
}