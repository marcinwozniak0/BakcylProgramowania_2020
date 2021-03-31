#include "search_func.hpp"
#include "utils.hpp"
#include <iostream>


std::vector<Card> searchFor(SearchFlags sf)
{
	std::string mainQuery = prepareSQLQuery(sf);
    std::vector<Card> cards = getCards(mainQuery);
	
	return cards;
}


std::vector<Card> getCards(std::string mainQuery)
{
    std::vector<Card> cards = {};
    
    sqlite3* db;
	sqlite3_open("database.sql", &db);
    sqlite3_stmt* stmt;
    std::string fullQuery = "SELECT cardID.cardCode AS cardCode,   attack, cost, health,   "
	    "collectible, [set], descriptionRaw, levelupDescriptionRaw, flavorText, [name], supertype,   gameAbsolutePath, "
	    "fullAbsolutePath FROM " + mainQuery + " AS cardID NATURAL JOIN cards NATURAL JOIN cardAssets;";
    
    int exit = sqlite3_prepare_v2(db, fullQuery.c_str(), -1, &stmt, NULL);
    errorHandler(exit, db);
    
    while((exit = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        cards.push_back(turnIntoCard(stmt));
    }
    errorHandler(exit, db);
    
    sqlite3_finalize(stmt);
    
    return cards;
}

Card turnIntoCard(sqlite3_stmt* stmt)
{
    int i = 0;
    Card card;
	card.setCardCode( toStr( sqlite3_column_text(stmt, i++) ) );
    //card.setRegionRef( toStr( sqlite3_column_text(stmt, i++) ) );
    card.setAttack( sqlite3_column_int(stmt, i++) );
    card.setCost( sqlite3_column_int(stmt, i++) );
    card.setHealth( sqlite3_column_int(stmt, i++) );
    //card.setSpellSpeedRef( toStr( sqlite3_column_text(stmt, i++) ) );
    //card.setRarityRef( toStr( sqlite3_column_text(stmt, i++) ) );
    card.setCollectible( sqlite3_column_int(stmt, i++) );
    card.setSet( toStr( sqlite3_column_text(stmt, i++) ) );
    card.setDescriptionRaw( toStr( sqlite3_column_text(stmt, i++) ) );
    card.setLevelupDescriptionRaw( toStr( sqlite3_column_text(stmt, i++) ) );
    card.setFlavorText( toStr( sqlite3_column_text(stmt, i++) ) );
    card.setName( toStr( sqlite3_column_text(stmt, i++) ) );
    card.setSupertype( toStr( sqlite3_column_text(stmt, i++) ) );
    //card.setType( toStr( sqlite3_column_text(stmt, i++) ) );
    
    std::map<std::string, std::string> assets;
    assets["gameAbsolutePath"] = toStr( sqlite3_column_text(stmt, i++) );
    assets["fullAbsolutePath"] = toStr( sqlite3_column_text(stmt, i) );
    card.setCardAssets( assets );
    
    //add keywords, subtypes and associated cards
	
	return card;
}


std::string prepareSQLQuery(SearchFlags sf)
{
	std::string query = "(SELECT cardCode FROM cards LIMIT 40)";
	//make query according to the search flags

	return query;
}
