#pragma once
#include <string>
#include <vector>
#include <map>
#include <optional>

#include "Deck.hpp"
#include "../../ErrorWindow.h"



class DeckBuilder 
{
   private:
    int maxNumberOfCards = 40;
    int maxNumberOfHeroes = 6;
    int maxNumberOfEachCard = 3;
    int heroDef;
    CardApi::Region firstRegion {};
    CardApi::Region secondRegion {};
    std::map <CardApi::Card, int> cardCount;
    Deck deck;

   public:
    void addCard(CardApi::Card& cardToAdd);
    void removeCard(CardApi::Card& cardToRemove);
    void addCardByID (SqliteHelper::unique_sqlite3& db, const std::string& cardCode);
    void removeCardByID (SqliteHelper::unique_sqlite3& db, const std::string& cardCode);
    int checkNumberOfCard(CardApi::Card card);
    int getDeckLength(){return deck.length();}

    Deck getDeck(){return deck;}
}; 

