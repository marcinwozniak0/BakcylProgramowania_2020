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
        if(x >= (int)cards.size())break;

        std::cout << "cardCode: " << cards.at(x).getCardCode() << std::endl;
        std::cout << "name: " << cards.at(x).getName() << std::endl;
        std::cout << "health: " << cards.at(x).getHealth() << std::endl;
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
    
    while(true)
    {
        std::string code;
        std::cin >> code;
        Card card = getCard(code);
        
            std::cout << "cardCode: " << card.getCardCode() << std::endl;
            std::cout << "name: " << card.getName() << std::endl;
            std::cout << "health: " << card.getHealth() << std::endl;
            std::cout << "description: " << card.getDescriptionRaw() << std::endl;
            std::cout << "keywords: ";
            for(uint i = 0; i < card.getCardKeywords().size(); ++i)
            {
                if(i != 0)std::cout << ", ";
                std::cout << card.getCardKeywords().at(i);
            }
            std::cout << std::endl;
            std::cout << "set: " << card.getSet() << std::endl;
    }  
    //these are just tests, don't kill me for that ugly code  
    
    return 0;
}
