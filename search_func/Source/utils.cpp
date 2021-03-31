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
    std::string str(reinterpret_cast<const char*> (chain));
    return str;
}
