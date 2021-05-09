#pragma once
#include <string>
#include <vector>
#include <map>
#include "Card.hpp"
#include "Deck.hpp"

class DeckBuilder 
{
    private:
    int maxNumberOfCards;
    int maxNumberOfHeroes;
    int maxNumberOfEachCard;
    int heroDef;
    std::string firstRegion;
    std::string secondRegion;
    std::map <Card, int> cardCount;
    Deck deck;
    int checkNumberOfCard(Card card);

    public:
    DeckBuilder();
    ~DeckBuilder();
    int getDeckLength()
    {
        return deck.length();
    }
    void addCard(Card &cardToAdd);
    void removeCard(Card &cardToRemove);
}; 

