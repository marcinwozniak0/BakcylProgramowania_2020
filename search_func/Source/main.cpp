#include <iostream>
#include <iostream>
#include <sqlite3.h>
#include "search_func.hpp"

	
int main()
{
    SearchRequest sr;
    std::vector<Card> cards = searchFor(sr);
    std::cout << cards.size()<< std::endl;
    while(true)
    {
        int x;
        std::cin >> x;

        std::cout << "cardCode: " << cards.at(x).getCardCode() << std::endl;
        std::cout << "name: " << cards.at(x).getName() << std::endl;
        std::cout << "description: " << cards.at(x).getDescriptionRaw() << std::endl;
        std::cout << "keywords: ";
        for(uint i = 0; i < cards.at(x).getCardKeywords().size(); ++i)
        {
            if(i != 0)std::cout << ", ";
            std::cout << cards.at(x).getCardKeywords().at(i);
        }
        std::cout << std::endl;
        std::cout << "set: " << cards.at(x).getSet() << std::endl;
    }

    return 0;
}
