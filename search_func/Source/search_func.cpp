#include <sqlite3.h>
#include "Card.hpp"
#include "SearchFlags.hpp"

std::vector<Card> results;


std::string toString(std::size_t x)
{
	std::string s = "";
	while(x > 0)
	{
		s = (char)(x % 10 + '0') + s;
		x /= 10;
	}

	return s;
}

std::string prepareSQLQuery(SearchFlags sf)
{
	std::string query = "SELECT cardCode FROM 'cards' WHERE ";
	bool where_searches = 0;

	if(sf.hp >= 0)
	{
		query += "health = 0 AND ";
		where_searches = true;
	}
	else if(sf.hpMin >= 0 && sf.hpMax >= 0)
	{
		query += "health >= " + toString(sf.hpMin) + " AND health <= " + toString(sf.hpMax) + " AND ";
		where_searches = true;
	}

	//other flags
	
	query = query.substr(0, query.size() - 4);

	return query;
}
