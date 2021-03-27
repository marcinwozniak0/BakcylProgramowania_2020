#include "search_func.hpp"
#include "utils.hpp"
#include <iostream>

std::vector<Card> results = {};

std::vector<Card> searchFor(SearchFlags sf)
{
	sqlite3* db;
	sqlite3_open("database.sql", &db);
	std::string mainQuery = prepareSQLQuery(sf);
	std::string fullQuery = "SELECT * FROM cards NATURAL JOIN ("
		+ mainQuery + ");";
	int exit = sqlite3_exec(db, fullQuery.c_str(), fillResultArrayWCards, NULL, NULL);
	if(exit != SQLITE_OK)
	{
		std::cout << "Sth's up w/ the db" << std::endl;
	}

	//assets, subtypes etc
	
	std::vector<Card> cards = results;
	return cards;
}


Card turnIntoCard(char** data, std::vector<std::string> colNames)
{
    Card card;
	card.setCardCode(data[find(colNames, "cardCode")]);
	//set rest of card
	
	return card;
}


int fillResultArrayWCards(void* unused, int colCount, char** data, char** _colNames)
{
	std::vector<std::string> colNames(colCount);
	for(int i = 0; i < colCount; ++i)
	{
		std::string str(_colNames[i]);
		colNames[i] = str;
	}

	Card card = turnIntoCard(data, colNames);
	
	results.push_back(card);
	
	return 0;
}


std::string prepareSQLQuery(SearchFlags sf)
{
	std::string query = "SELECT cardCode FROM 'cards' WHERE ";
	bool where_searches = false;

	if(sf.hp >= 0)
	{
		query += "health = " + std::to_string(sf.hp) + " AND ";
		where_searches = true;
	}
	else if(sf.hpMin >= 0 && sf.hpMax >= 0)
	{
		query += "health >= " + std::to_string(sf.hpMin) +
		       	" AND health <= " + std::to_string(sf.hpMax) + " AND ";
		where_searches = true;
	}

	//other flags
	
	if(where_searches)
	{
		query = query.substr(0, query.size() - 4);
	}
	else 
	{
	    query = query.substr(0, query.size() - 6);
	}

	return query;
}
