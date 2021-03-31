#include <iostream>
#include <sqlite3.h>
#include "search_func.hpp"

	
int main()
{
    SearchFlags sf;
    std::vector<Card> cards = searchFor(sf);
    std::cout << cards.at(19).getCardCode() << std::endl;
    std::cout << cards.at(19).getName() << std::endl;
    std::cout << cards.at(19).getDescriptionRaw() << std::endl;
    std::cout << cards.at(19).getSupertype() << std::endl;
    
    return 0;
}
