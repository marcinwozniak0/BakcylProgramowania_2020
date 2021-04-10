#include "search_func.hpp"
#include "utils.hpp"
#include <iostream>
#include <memory>


std::string mainQuery = "SELECT cardCode, " /*regions.name, */  "attack, cost, health, " /*spellSpeeds.name, */
	    /*rarities.name, */ "collectible, sets.name, descriptionRaw, levelupDescriptionRaw, flavorText, "
	    "cards.name, supertype, " /*type, */ "gameAbsolutePath, fullAbsolutePath FROM cards NATURAL JOIN "
	    "cardAssets LEFT JOIN regions ON regionRef = regions.nameRef LEFT JOIN spellSpeeds ON spellSpeedRef = "
	    "spellSpeeds.nameRef LEFT JOIN rarities ON rarityRef = rarities.nameRef LEFT JOIN sets ON [set] = sets.nameRef ";
	    
	    
Card getCard(std::string cardCode)
{
    std::string sqlQuery = mainQuery + "WHERE cardCode = '" + cardCode + "';";
    std::vector<Card> cards = getCards(sqlQuery);
    
    if(cards.size() == 0)
    {
        Card card;
        return card;
    }
    
    return cards.at(0);
}
    

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
	std::string query = mainQuery + "WHERE ";
	
	/********* untested *************
	if(sr.name != "")
	{
	    query += "cards.name = '" + sr.name_ + "';";
	    return query;
	}
	
	
	std::map<std::string, std::vector<int> > iAttr;                 //int attributes
	std::vector<std::string> names = {"health", "cost", "attack"};  //attributes' names
	
	iAttr[names.at(0)] = {sr.hp_, sr.hpMin_, sr.hpMax_};
	iAttr[names.at(1)] = {sr.cost_, sr.costMin_, sr.costMax_};
	iAttr[names.at(2)] = {sr.atack_, sr.atackMin_, sr.atackMax_};
	
	for(int i = 0; i < 3; ++i)
	{
	    if(iAttr[names.at(i)].at(0) != 0)
	    {
	        query += names.at(i) + " = " + iAttr[names.at(i)].at(0) + " AND ";
	    }
	    else
	    {
	        if(sr.hpMin_ != 0)
	        {
	            query += names.at(i) + " >= " + iAttr[names.at(i)].at(1) + " AND ";
	        }
	        if(sr.hpMax_ != 0)
	        {
	            query += names.at(i) + " <= " + iAttr[names.at(i)].at(2) + " AND ";
	        }
	    }
	} ***********************************/
	
	//finish query according to SearchRequest
	
	if(query[query.size() - 2] == 'E')
	{
	    query = query.substr(0, query.size() - 6);
	}
	else
	{
	    query = query.substr(0, query.size() - 4);
	}
	query += "ORDER BY cards.name LIMIT 40;";

	return query;
}
