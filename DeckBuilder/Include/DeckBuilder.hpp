#pragma once
#include <string>
#include <vector>
#include <map>
#include <optional>

#include "Deck.hpp"



class DeckBuilder 
{
   private:
    int maxNumberOfCards = 40;
    int maxNumberOfHeroes = 6;
    int maxNumberOfEachCard = 3;
    int heroDef;
    std::map <CardApi::Card, int> cardCount;
    Deck deck;

   public:
    CardApi::Region firstRegion {};
    CardApi::Region secondRegion {};
    void addCard(CardApi::Card& cardToAdd);
    void removeCard(CardApi::Card& cardToRemove);
    void addCardByID (SqliteHelper::unique_sqlite3& db, const std::string& cardCode);
    void removeCardByID (SqliteHelper::unique_sqlite3& db, const std::string& cardCode);
    int checkNumberOfCard(CardApi::Card card);
    int getDeckLength(){return deck.length();}
    std::map<CardApi::Card, int> getCardCountMap();
    Deck getDeck(){return deck;}
}; 

