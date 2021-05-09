#pragma once
#include <string>
#include <vector>
#include <map>
#include "Card.hpp"
#include "Deck.hpp"
#include "baseCardApi.hpp"

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

    public:
    DeckBuilder();
    ~DeckBuilder();
    void addCard(Card &cardToAdd);
    void removeCard(Card &cardToRemove);
    void addCardByID (SqliteHelper::unique_sqlite3& db, const std::string& cardCode);
    void removeCardByID (SqliteHelper::unique_sqlite3& db, const std::string& cardCode);
    int checkNumberOfCard(Card card);
}; 

