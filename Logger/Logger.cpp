#include <iostream>
#include <fstream>
<<<<<<< HEAD
#include <cstdio>
#include <ctime>
=======
>>>>>>> c0bf52b51258c615b489034738f7da36605fa796
#include "Logger.hpp"

enum exceptionLevel
{
	fine = 0,
	warning = 1,
	error = 2,
	fatal = 3
};

<<<<<<< HEAD
const std::string currentDateTime() 
{
    time_t now = time(0);
    struct tm  tstruct;
    char currentTime[80];
    tstruct = *localtime(&now);
    strftime(currentTime, sizeof(currentTime), "[%Y-%m-%d %X]", &tstruct);

    return currentTime;
}

=======
>>>>>>> c0bf52b51258c615b489034738f7da36605fa796
void Logger::log(const std::string& msg, const int exc)
{
    if (logs.is_open())
    {     
<<<<<<< HEAD
        logs << currentDateTime() << " " << msg << "\n\n";
=======
    

    
    
        logs << msg << "\n";
>>>>>>> c0bf52b51258c615b489034738f7da36605fa796
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
