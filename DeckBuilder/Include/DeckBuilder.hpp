#pragma once
#include <string>
#include <vector>
#include <map>
#include <optional>

#include "Deck.hpp"
#include "ErrorWindow.h"
#include "base64.h"

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
    void removeCardStack(CardApi::Card& cardToRemove);
    void removeCardByID (SqliteHelper::unique_sqlite3& db, const std::string& cardCode);
    int checkNumberOfCard(CardApi::Card card);
    int getDeckLength(){return deck.length();}
    std::string getEncodedDeck();
    void setFromEncoded(SqliteHelper::unique_sqlite3& db, std::string encodedDeck);
    void resetDeck();
    std::map<CardApi::Card, int> getCardCountMap();
    Deck getDeck(){return deck;}
}; 
