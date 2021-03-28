#include <iostream>
#include <sqlite3.h>
#include "search_func.hpp"


int nwzn()
{
    sqlite3* db;
    sqlite3_open("database.sql", &db);
    
    std::string query = "SELECT cardCode, attack, cost, health, "
	    "collectible, [set], descriptionRaw, levelupDescriptionRaw, flavorText, "
	    "[name], supertype, gameAbsolutePath, fullAbsolutePath FROM cards NATURAL JOIN "
	    "cardAssets WHERE cardCode = '01IO012';" ;
	    
	//char* errMsg;
	int exit = sqlite3_exec(db, query.c_str(), fillResultArrayWCards, NULL, NULL);
	std::cout << results[0].getCardCode() << std::endl;
	std::cout << results[0].getName() << std::endl;
	
	sqlite3_close();
	return 0;
}
	
int main()
{
    nwzn();
    return 0;
}
