#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>

#include "Logger.hpp"

const std::string currentDateTime() 
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       currentTime[80];
    tstruct = *localtime(&now);
    strftime(currentTime, sizeof(currentTime), "%Y-%m-%d_%X", &tstruct);

    return currentTime;
}

void Logger::log(const std::string& msg)
{
    std::string fileName = "logs_" + currentDateTime() + ".txt";
    
    std::ofstream outfile(fileName);

    logs.open(fileName, std::ios::app);
        
    logs << msg << "\n";

    std::cout << msg << std::endl;
}

Logger::~Logger() 
{
    logs.close();
}

