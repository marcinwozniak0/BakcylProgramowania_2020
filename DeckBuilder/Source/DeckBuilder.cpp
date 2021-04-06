#include "DeckBuilder.hpp"

DeckBuilder::DeckBuilder()
{
    int maxNumberOfCards = 40;
    int maxNumberOfHeroes = 6;
    int maxNumberOfEachCard = 3;
}

int DeckBuilder::checkNumberOfCard(Card card) 
{
    int number = 0;
    for (Card c : deck.getCardsAsVector()) 
    {
        if (c == card) 
        {
            number++;
        }
    }
    return number;
}

void DeckBuilder::addCard(Card &cardToAdd)
{
    int dl = deck.length();
    if (dl < maxNumberOfCards && checkNumberOfCard(cardToAdd) < maxNumberOfEachCard) {
        if (firstRegion == "") 
        {
            firstRegion = cardToAdd.getRegion();
        } 
        else if (secondRegion == "") 
        {
            secondRegion = cardToAdd.getRegion();
        } 
        else if (!(firstRegion == cardToAdd.getRegion() || secondRegion == cardToAdd.getRegion())) 
        {
            throw new std::exception;                                       //TODO: change exception
            return;
        }

        if (cardToAdd.getType() == "hero" && maxNumberOfHeroes > 0) 
        {       //TODO: correct type
            maxNumberOfHeroes--;
            deck.addCard(cardToAdd);
        } 
        else 
        {
            deck.addCard(cardToAdd);
        }
    } 
    else 
    {
        throw new std::exception;                                            //TODO: change exception
    }
}

void removeCard(Card &cardToRemove)
{

}

DeckBuilder::~DeckBuilder() {}
