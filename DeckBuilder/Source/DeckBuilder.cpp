#include "DeckBuilder.hpp"
#include "Deck.hpp"

DeckBuilder::DeckBuilder()
{
    int maxNumberOfCards = 40;
    int maxNumberOfHeroes = 6;
    int maxNumberOfEachCard = 3;
    int heroDef = 2;
    std::string firstRegion = "";
    std::string secondRegion = "";
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
    int deckLength = deck.length();
    if (deckLength < maxNumberOfCards && checkNumberOfCard(cardToAdd) < maxNumberOfEachCard) 
    {
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

        if (cardToAdd.getType() == "hero" && deck.getNumberOfHeroes() < maxNumberOfHeroes) //TODO: correct type of hero, ask SQL(!)
        {       
            deck.increaseNumberOfHeroes();
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

void DeckBuilder::removeCard(Card &cardToRemove)
{
    int deckLength = deck.length();
    for (int i = 0; i < deckLength; i++)
    {
        if (deck.getCardsAsVector().at(i) == cardToRemove)
        {
            std::string cardRegion = cardToRemove.getRegion();

            if (cardToRemove.getType() == "hero")
            {
                deck.decreaseNumberOfHeroes();
            }

            deck.removeCard(i);
            
            int counter = 0;
            int deckLength = deck.length();
            for (int j = 0; j < deckLength; j++)
            {
                if(deck.getCardsAsVector().at(j).getRegion() == cardRegion)
                {
                    break;
                } 
                else 
                {
                    counter++;
                }
            }

            if (counter == deckLength)
            {
                if (firstRegion == cardRegion)
                {
                    firstRegion = "";
                    return;
                } 
                else if (secondRegion == cardRegion)
                {
                    secondRegion = "";
                    return;
                }
            }

            return;
        }
    }
}

DeckBuilder::~DeckBuilder() {}
