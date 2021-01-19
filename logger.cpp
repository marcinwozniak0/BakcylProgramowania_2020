#include <iostream>
#include <fstream>

#include "logger.hpp"

using namespace std;

void Logger::log(string msg)
{
    fstream logs;

    if (logs.good())
    {
        logs.open("logs.txt", ios::app);
        
        logs<<msg<<"\n";

        logs.close();
    }
    else
    {
        ofstream outfile("logs.txt");

        logs.open("logs.txt", ios::app);
        
        logs<<msg<<"\n";

        logs.close();
    }
    

    cout<<msg<<endl;
} 

