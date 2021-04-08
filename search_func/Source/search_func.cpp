#include "search_func.hpp"
#include "utils.hpp"
#include <iostream>


std::vector<Card> searchFor(SearchRequest sr)
{
	std::string sqlQuery = prepareSQLQuery(sr);
    std::vector<Card> cards = getCards(sqlQuery);

	return cards;
}


std::vector<Card> getCards(std::string sqlQuery)
{
    std::vector<Card> cards = {};
    
    sqlite3* db;
	sqlite3_open("database.sql", &db);
    sqlite3_stmt* stmt;
    
    int exit = sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &stmt, NULL);
    errorHandler(exit, db);
    
    while((exit = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        cards.push_back(turnIntoCard(stmt));
    }
    errorHandler(exit, db);
    sqlite3_finalize(stmt);
    
    for(Card& card : cards)
    {
        takePluralData(card, db);
    }
    sqlite3_close(db);
    
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
    
	return card;
}


void takePluralData(Card& card, sqlite3* db)
{
    sqlite3_stmt* stmt;
    std::string cardCode = card.getCardCode();
    
    std::string queries[3] = {"SELECT name FROM cardKeywords JOIN keywords "
        "ON keywordRef = nameRef WHERE cardCode = '" + cardCode + "';", 
        
        "SELECT subtype FROM cardSubtypes WHERE cardCode = '" + cardCode + "';", 
        
        "SELECT associatedCardCode FROM associatedCards WHERE cardCode = '" + cardCode + "';"};
        
    for(int i = 0; i < 3; ++i)
    {
        std::vector<std::string> data = {};
        
        int exit = sqlite3_prepare_v2(db, queries[i].c_str(), -1, &stmt, NULL);
        errorHandler(exit, db);
    
        while((exit = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            data.push_back( toStr( sqlite3_column_text(stmt, 0) ) );
        }
        errorHandler(exit, db);
        sqlite3_finalize(stmt);
        
        switch(i)
        {
            case 0: card.setCardKeywords(data); break;
            case 1: card.setCardSubtypes(data); break;
            //case 2: card.setAssociatedCards(data);
        }
    }
}


std::string prepareSQLQuery(SearchRequest sr)
{
	std::string query = "SELECT cardCode, " /*regions.name, */  "attack, cost, health, " /*spellSpeeds.name, */
	    /*rarities.name, */ "collectible, sets.name, descriptionRaw, levelupDescriptionRaw, flavorText, "
	    "cards.name, supertype, " /*type, */ "gameAbsolutePath, fullAbsolutePath FROM cards NATURAL JOIN "
	    "cardAssets LEFT JOIN regions ON regionRef = regions.nameRef LEFT JOIN spellSpeeds ON spellSpeedRef = "
	    "spellSpeeds.nameRef LEFT JOIN rarities ON rarityRef = rarities.nameRef LEFT JOIN sets ON [set] = sets.nameRef "
	    "ORDER BY cards.name LIMIT 40";
	    
	//make query according to the search request

	return query;
}
