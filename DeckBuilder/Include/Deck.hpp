#pragma once
#include <string>
#include <vector>
#include "Card.hpp"

class Deck
{
    private:
    int numberOfHeroes;
    std::string firstRegion;
    std::string secondRegion;
    std::vector <Card> deck;

    public:
    Deck();
    ~Deck();
    void addCard(Card &cardToAdd);
    void removeCard(int i);
    int length();
    std::vector <Card> getCardsAsVector();
    int getNumberOfHeroes();
    void increaseNumberOfHeroes();
    void decreaseNumberOfHeroes();
};