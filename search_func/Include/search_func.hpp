#pragma once
#include <sqlite3.h>
#include "Card.hpp"
#include "SearchFlags.hpp"


extern std::vector<Card> results;

std::vector<Card> searchFor(SearchFlags);
Card turnIntoCard(char**, std::vector<std::string>);
static int fillResultArrayWCards(void*, int, char**, char**);
std::string prepareSQLQuery(SearchFlags);
std::string toString(std::size_t);
