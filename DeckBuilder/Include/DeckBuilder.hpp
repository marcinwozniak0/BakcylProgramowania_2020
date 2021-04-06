#pragma once
#include <string>
#include <vector>
#include <map>
#include "Card.hpp"
#include "Deck.hpp"
#include "Logger.hpp"
#include "ExceptionLevels.cpp"

class DeckBuilder 
{
    private:
    int maxNumberOfCards;
    int maxNumberOfHeroes;
    int maxNumberOfEachCard;
    int heroDef;
    std::string firstRegion;
    std::string secondRegion;
    std::map<Card,int> cardCount;
    Deck deck;
    int checkNumberOfCard(Card card);

    public:
    DeckBuilder();
    ~DeckBuilder();
    void addCard(Card &cardToAdd);
    void removeCard(Card &cardToRemove);
}; 

