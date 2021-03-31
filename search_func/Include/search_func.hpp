#pragma once
#include <sqlite3.h>
#include "Card.hpp"
#include "SearchFlags.hpp"


std::vector<Card> searchFor(SearchFlags);
Card turnIntoCard(sqlite3_stmt*);
std::vector<Card> getCards(std::string);
std::string prepareSQLQuery(SearchFlags);
