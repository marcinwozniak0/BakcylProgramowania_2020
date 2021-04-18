#pragma once
#include <sqlite3.h>
#include "Card.hpp"
#include "search_flags.hpp"


extern std::string mainQuery;


Card getCard(std::string);
std::vector<Card> searchFor(searchFlags);

struct Query
{
    std::string text;
    std::vector<int> bindings;
    //int pageNr;
};

std::vector<Card> getCards(Query);
Card turnIntoCard(sqlite3_stmt*);
void takePluralData(Card&, sqlite3*);
Query prepareSQLQuery(searchFlags);
