#include <iostream>
#include <fstream>
#include "Logger.hpp"

enum exceptionLevel
{
	fine = 0,
	warning = 1,
	error = 2,
	fatal = 3
};

void Logger::log(const std::string& msg, const int exc)
{
    if (logs.is_open())
    {     
    

    
    
        logs << msg << "\n";
    }
    else
    {
        std::ofstream outfile("logs.txt");

        logs.open("logs.txt", std::ios::app);
        
        logs << msg << "\n";
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

