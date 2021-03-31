#pragma once
#include <sqlite3.h>
#include "Card.hpp"
#include "SearchFlags.hpp"


std::vector<Card> searchFor(SearchFlags);
std::vector<Card> getCards(std::string);
Card turnIntoCard(sqlite3_stmt*);
void takePluralData(Card&, sqlite3*);
std::string prepareSQLQuery(SearchFlags);
