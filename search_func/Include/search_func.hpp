#pragma once
#include <sqlite3.h>
#include "Card.hpp"
#include "search_flags.hpp"


extern std::string mainQuery;


Card getCard(std::string);
std::vector<Card> searchFor(searchFlags);

std::vector<Card> getCards(std::string);
Card turnIntoCard(sqlite3_stmt*);
void takePluralData(Card&, sqlite3*);
std::string prepareSQLQuery(searchFlags);
