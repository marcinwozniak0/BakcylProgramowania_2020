#pragma once
#include <string>
#include <vector>
#include <map>
#include "Card.hpp"
#include "Deck.hpp"
#include "../../db/card_api/Include/baseCardApi.hpp"


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
    void addCard(std::optional<CardApi::Card>& cardToAdd);
    void removeCard(std::optional<CardApi::Card>& cardToRemove);
    void addCardByID (SqliteHelper::unique_sqlite3& db, const std::string& cardCode);
    void removeCardByID (SqliteHelper::unique_sqlite3& db, const std::string& cardCode);
    int checkNumberOfCard(Card card);
}; 

