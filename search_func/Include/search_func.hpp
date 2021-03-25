#include <sqlite3.h>
#include "Card.cpp"
#include "SearchFlags.hpp"


extern std::vector<Card> results;

std::vector<Card> searchFor(SearchFlags sf);
static int turnIntoCard(void* unused, int colCount, char** data, char** colNames);
std::string prepareSQLQuery(SearchFlags sf);
