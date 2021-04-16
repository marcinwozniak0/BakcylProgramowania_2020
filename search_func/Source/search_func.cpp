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
    std::string sqlQuery = mainQuery + "WHERE cardCode = '" + cardCode + "';";
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
    std::string sqlQuery = prepareSQLQuery(sf);
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


std::string prepareSQLQuery(searchFlags sf)
{
	std::string query = mainQuery + "WHERE ";
	
	//********* untested *************
	
	if(sf.name != "")   //i'm thinking about automating this later
	{
	    query += "(cards.name LIKE '%" + sf.name + "%' OR "
	            "regions.name LIKE '%" + sf.name + "%') AND ";
	}
	
	
	std::map<std::string, searchFlags::intmember> iMemb;  //int members
	//std::string names[3] = {"health", "cost", "attack"};    //attributes' names
	
	iMemb["health"] = sf.hp;
	iMemb["cost"] = sf.cost;
	iMemb["attack"] = sf.attack;
	
	for(auto [name, member] : iMemb)
	{
	    if(member.value != std::nullopt)
	    {
	        query += name + " = " + (char)('0' + member.value.value()) + " AND ";   //conversions only temporary
	    }
	    else
	    {
	        if(member.min != std::nullopt)
	        {
	            query += name + " >= " + (char)('0' + member.min.value()) + " AND ";
	        }
	        if(member.max != std::nullopt)
	        {
	            query += name + " <= " + (char)('0' + member.max.value()) + " AND ";
	        }
	    }
	} 
	
	
	std::map<std::string, std::vector<std::string> > sMemb; //string members
	//names = {"rarities.name", "type", "regions.name"};
	
	sMemb["rarities.name"] = sf.rarities;
	sMemb["type"] = sf.types;
	sMemb["regions.name"] = sf.regions;
	
	for(auto [name, member] : sMemb)
	{
	    if(member.empty() == false)
	    {
	        query += "(";
	        for(std::string value : member)
	        {
	            query += name + " = '" + value + "' OR ";
	        }
	        query = query.substr(0, query.size() - 4) + ") AND ";
	    }
	}
	
	if(query[query.size() - 2] == 'D')  //i'll also try to go around this later
	{
	    query = query.substr(0, query.size() - 4);
	}
	else
	{
	    query = query.substr(0, query.size() - 6);
	}
	query = query + "ORDER BY cards.name LIMIT (" + (char)(sf.pageNr - 1 + '0') + " * 15), 15;";
	                                         //i'll probably use bind on that later, it'll be more safe
	                                         //and we'll be able to have two digit pageNr
	                                         //also maybe we could multi-bind it and get other pages faster
	                                         //without having to go through this whole function again
	
	//***********************************/
	
	//finish query according to SearchRequest
	
	//query += "sets.name LIKE '_ou%' ORDER BY cards.name LIMIT 15;";
    std::cout << query << std::endl;
	return query;
}
