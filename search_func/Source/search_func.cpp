#include "search_func.hpp"
#include <iostream>

std::vector<Card> results = {};

std::vector<Card> searchFor(SearchFlags sf)
{
	sqlite3* db;
	sqlite3_open("database.sql", &db);
	std::string mainQuery = prepareSQLQuery(sf);
	std::string fullQuery = "SELECT * FROM cards WHERE cardCode IN ("
		+ mainQuery + ");";
	int exit = sqlite3_exec(db, fullQuery.c_str(), turnIntoCard, NULL, NULL);
	if(exit != SQLITE_OK)
	{
		std::cout << "Sth's up w/ the db" << std::endl;
	}

	//assets, subtypes etc
	
	std::vector<Card> cards = results;
	return cards;
}

unsigned int find(std::vector<std::string> vector, std::string value)
{
    int i;
	for(i = 0; i < (int)vector.size(); ++i)
	{
		if(vector[i] == value)
		{
			break;
		}
	}
	if(i > (int)vector.size()) return -1;
	return i;
}

static int turnIntoCard(void* unused, int colCount, char** data, char** _colNames)
{
	std::vector<std::string> colNames(colCount);
	for(int i = 0; i < colCount; ++i)
	{
		std::string str(_colNames[i]);
		colNames[i] = str;
	}

	Card card;
	card.setCardCode(data[find(colNames, "cardCode")]);
	//set rest of card
	
	results.push_back(card);
	
	return 0;
}

std::string toString(std::size_t x)
{
	std::string s = "";
	while(x > 0)
	{
		s = (char)(x % 10 + '0') + s;
		x /= 10;
	}
	return s;
}

std::string prepareSQLQuery(SearchFlags sf)
{
	std::string query = "SELECT cardCode FROM 'cards' WHERE ";
	bool where_searches = 0;

	if(sf.hp >= 0)
	{
		query += "health = 0 AND ";
		where_searches = true;
	}
	else if(sf.hpMin >= 0 && sf.hpMax >= 0)
	{
		query += "health >= " + toString(sf.hpMin) +
		       	" AND health <= " + toString(sf.hpMax) + " AND ";
		where_searches = true;
	}

	//other flags
	
	if(where_searches)
	{
		query = query.substr(0, query.size() - 4);
	}
	else query = query.substr(0, query.size() - 6);

	return query;
}
