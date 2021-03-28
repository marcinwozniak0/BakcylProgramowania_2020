#include "search_func.hpp"
#include "utils.hpp"
#include <iostream>

std::vector<Card> results = {};

std::vector<Card> searchFor(SearchFlags sf)
{
	sqlite3* db;
	sqlite3_open("database.sql", &db);
	std::string mainQuery = prepareSQLQuery(sf);
	std::string fullQuery = "SELECT cardID.cardCode AS cardCode, regionRef, attack, cost, health, spellSpeedRef, rarityRef, "
	    "collectible, [set], descriptionRaw, levelupDescriptionRaw, flavorText, [name], supertype, [type], gameAbsolutePath, "
	    "fullAbsolutePath FROM (" + mainQuery + ") AS cardID NATURAL JOIN cards NATURAL JOIN cardAssets;";
	    
	int exit = sqlite3_exec(db, fullQuery.c_str(), fillResultArrayWCards, NULL, NULL);
	if(exit != SQLITE_OK)
	{
		std::cout << "Sth's up w/ the db" << std::endl;
	}

	//assets, subtypes etc
	
	std::vector<Card> cards = results;
	return cards;
}


Card turnIntoCard(std::string* data)
{
    Card card;
	card.setCardCode( *data++ );
    //card.setRegionRef( *data++ );
    card.setAttack( std::stoi(*data++) );
    card.setCost( std::stoi(*data++) );
    card.setHealth( std::stoi(*data++) );
    //card.setSpellSpeedRef( *data++ );
    //card.setRarityRef( *data++ );
    card.setCollectible( std::stoi(*data++) );
    card.setSet( *data++ );
    card.setDescriptionRaw( *data++ );
    card.setLevelupDescriptionRaw( *data++ );
    card.setFlavorText( *data++ );
    card.setName( *data++ );
    card.setSupertype( *data++ );
    //card.setType( *data++ );
    
    std::map<std::string, std::string> assets;
    assets["gameAbsolutePath"] = *data++;
    assets["fullAbsolutePath"] = *data++;
    card.setCardAssets( assets );
	
	return card;
}


int fillResultArrayWCards(void* unused, int colCount, char** _data, char** colNames)
{
    std::string* data = new std::string[colCount];
	for(int i = 0; i < colCount; ++i)
	{
	    std::string str(_data[i]);
		data[i] = str;
	}

	Card card = turnIntoCard(data);
	
	results.push_back(card);
	
	delete (data - colCount);   //won't work until fields are commented
	
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
