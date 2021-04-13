#include "utils.hpp"


void errorHandler(int exit, sqlite3* db)
{
    if(exit != SQLITE_OK && exit != SQLITE_DONE)
    {
        std::cout << "error: " << sqlite3_errmsg(db) << std::endl;
    }
}


std::string toStr(const unsigned char* chain)
{
    if(chain == NULL)
    {
        return "";
    }
    std::string str(reinterpret_cast<const char*> (chain));
    return str;
}


template<int size>
std::vector<std::string> bitsetToVec(std::bitset<size> bitSet, std::string name)
{
    std::map<std::string, std::vector<std::string> > values;
    values["rarities.name"] = {};   //list all regions
    values["type"] = {};            //list all types
    values["regions.name"] = {};    //list all regions
    
    //we can probably automate this later, so it takes eg. regions from
    //the latest globals.json file
    //or we can send values as one of the arguments of this function,
    
    std::vector<std::string> result;
    for(int i = 0; i < bitSet.size(); ++i)
    {
        if(bitSet[i] == true)
        {
            result.push_back(values[name].at(i));
        }
    }
    
    return result;
}
