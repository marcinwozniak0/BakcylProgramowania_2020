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
    std::string getEncodedDeck();
    void setFromEncoded(SqliteHelper::unique_sqlite3& db, std::string encodedDeck);

    Deck getDeck(){return deck;}
}; 