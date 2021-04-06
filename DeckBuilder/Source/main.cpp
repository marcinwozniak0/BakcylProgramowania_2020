#include "DeckBuilder.hpp"

int main()
{
    DeckBuilder db;
    Card card1;
    card1.setRegion("1");
    Card card2;
    card1.setRegion("2");
    Card card3;
    card1.setRegion("1");
    db.addCard(card1);
    db.addCard(card2);
    db.addCard(card3);
    std::cout << card3.getRegion();
    
    return 0;
}