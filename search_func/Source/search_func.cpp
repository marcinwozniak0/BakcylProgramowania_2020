#include "search_func.hpp"
#include "utils.hpp"
#include <iostream>
#include <memory>


std::string mainQuery = "SELECT cardCode, regions.name, attack, cost, health, spellSpeeds.name, "
	    "rarities.name, collectible, sets.name, descriptionRaw, levelupDescriptionRaw, flavorText, "
	    "cards.name, supertype, type, gameAbsolutePath, fullAbsolutePath FROM cards NATURAL JOIN "
	    "cardAssets LEFT JOIN regions ON regionRef = regions.nameRef LEFT JOIN spellSpeeds ON spellSpeedRef = "
	    "spellSpeeds.nameRef LEFT JOIN rarities ON rarityRef = rarities.nameRef LEFT JOIN sets ON [set] = sets.nameRef ";
	    
	    
Card getCard(std::string cardCode)
{
    Query sqlQuery;
    sqlQuery.text = (mainQuery + "WHERE cardCode = '" + cardCode + "';").c_str();
    std::vector<Card> cards = getCards(sqlQuery);
    
    if(cards.empty())
    {
        Card card;
        return card;
    }
    
    return cards.front();
}
    

std::vector<Card> searchFor(searchFlags sf)
{
    Query sqlQuery = prepareSQLQuery(sf);
    std::vector<Card> cards = getCards(sqlQuery);

	return cards;
}


std::vector<Card> getCards(Query sqlQuery)
{
    std::vector<Card> cards = {};
    
    sqlite3* db;
	sqlite3_open("database.sql", &db);
    sqlite3_stmt* stmt;
    
    int exit = sqlite3_prepare_v2(db, sqlQuery.text.c_str(), -1, &stmt, NULL);
    errorHandler(exit, db);
    
    for(unsigned int i = 0; i < sqlQuery.bindings.size(); ++i)
    {
        exit = sqlite3_bind_int(stmt, i + 1, sqlQuery.bindings.at(i));
        errorHandler(exit, db);
    }
    
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
    card.setRegion( toStr( sqlite3_column_text(stmt, i++) ) );
    card.setAttack( sqlite3_column_int(stmt, i++) );
    card.setCost( sqlite3_column_int(stmt, i++) );
    card.setHealth( sqlite3_column_int(stmt, i++) );
    card.setSpellSpeed( toStr( sqlite3_column_text(stmt, i++) ) );
    card.setRarity( toStr( sqlite3_column_text(stmt, i++) ) );
    card.setCollectible( sqlite3_column_int(stmt, i++) );
    card.setSet( toStr( sqlite3_column_text(stmt, i++) ) );
    card.setDescriptionRaw( toStr( sqlite3_column_text(stmt, i++) ) );
    card.setLevelupDescriptionRaw( toStr( sqlite3_column_text(stmt, i++) ) );
    card.setFlavorText( toStr( sqlite3_column_text(stmt, i++) ) );
    card.setName( toStr( sqlite3_column_text(stmt, i++) ) );
    card.setSupertype( toStr( sqlite3_column_text(stmt, i++) ) );
    card.setType( toStr( sqlite3_column_text(stmt, i++) ) );
    
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
            case 2: card.setAssociatedCards(data);
        }
    }
}


Query prepareSQLQuery(searchFlags sf)
{
    Query sqlQuery;

	std::string query = mainQuery + "WHERE "
	    "cards.name LIKE '%" + sf.name + "%' AND ";
	
	
	std::map<std::string, searchFlags::intmember> iMemb;  //int members
	
	iMemb["health"] = sf.hp;
	iMemb["cost"] = sf.cost;
	iMemb["attack"] = sf.attack;
	
	for(auto [name, member] : iMemb)
	{
	    if(member.value != std::nullopt)
	    {
	        query += name + " = ? AND ";
	        sqlQuery.bindings.push_back(member.value.value());
	    }
	    else
	    {
	        if(member.min != std::nullopt)
	        {
	            query += name + " >= ? AND ";
	            sqlQuery.bindings.push_back(member.min.value());
	        }
	        if(member.max != std::nullopt)
	        {
	            query += name + " <= ? AND ";
	            sqlQuery.bindings.push_back(member.max.value());
	        }
	    }
	} 
	
	
	std::map<std::string, std::vector<std::string> > sMemb; //string members
	
	sMemb["rarities.name"] = sf.rarities;
	sMemb["type"] = sf.types;
	sMemb["regions.name"] = sf.regions;
	
	for(auto [name, member] : sMemb)
	{
	    if(member.empty() == false)
	    {
	        query += name + " IN (";
	        for(std::string value : member)
	        {
	            query += "'" + value + "', ";
	        }
	        query = query.substr(0, query.size() - 2) + ") AND ";
	    }
	}
	
	
	query = query.substr(0, query.size() - 4) + 
	    "ORDER BY cards.name LIMIT (? * 15), 15;";
	sqlQuery.bindings.push_back(sf.pageNr - 1);
	//also maybe we could multi-bind it and get other pages faster
	//without having to go through this whole function again
	
	
    sqlQuery.text = query;
	return sqlQuery;
}
