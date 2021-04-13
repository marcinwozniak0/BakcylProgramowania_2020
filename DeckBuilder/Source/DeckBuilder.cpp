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
    int dl = deck.length();
    if (dl < maxNumberOfCards && checkNumberOfCard(cardToAdd) < maxNumberOfEachCard) 
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

        if (cardToAdd.getType() == "hero" && maxNumberOfHeroes > 0) 
        {       //TODO: correct type
            maxNumberOfHeroes--; //idk if this is correct i think it should be deck.numberOfHeroes++;
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
    int dl = deck.length();
    for (int i = 0; i < dl; i++)
    {
        //if (deck[i].getCardCode() == cardToRemove.getCardCode()) //mistake (i think) cant compare strings that way
        if (Deck::deck.at(i).getCardCode().compare(cardToRemove.getCardCode()) == 0)
        {
            string regioncd = deck[i].region;
            if (getCardsAsVector.at(i).getType().compare("hero"))
            {
                maxNumberOfHeroes++; //idk if this is correct should be deck.numberOfHeroes--;
            }
            deck.erase(i);
            maxNumberOfCards++; //idk if this is correct should be deck.numberOfCards--;
            int counter = 0;
            for (int j = 0; j < dl; j++)
            {
                if(deck[j].getRegion.compare(regioncd) == 0)
                {
                    break;
                } 
                else 
                {
                    counter++;
                }
            }

            dl = deck.length();
            if (counter == dl)
            {
                if (firstRegion.compare(regioncd) == 0)
                {
                    firstRegion = "";
                    return;
                } 
                else if (secondRegion.compare(regioncd) == 0)
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
