#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include "Logger.hpp"

enum exceptionLevel
{
	fine = 0,
	warning = 1,
	error = 2,
	fatal = 3
};

const std::string currentDateTime() 
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       currentTime[80];
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
    
    if(exc == exceptionLevel(fine)){
    	std::cout <<"FINE: "; 
	}
    if(exc == exceptionLevel(warning)){
    	std::cout <<"WARNING: "; 
	}	
    if(exc == exceptionLevel(error)){
    	std::cout <<"ERROR: "; 
	}
    if(exc == exceptionLevel(fatal)){
    	std::cout <<"FATAL ERROR: "; 
	}
    std::cout << msg << std::endl;
}

Logger::~Logger() {
logs.close();
}

int main()
{
    Logger logger;
    logger.log("test", 1);
    logger.log("??", 2);
    return 0;
}
