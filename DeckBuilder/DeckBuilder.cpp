#include "DeckBuilder.hpp"
DeckBuilder::DeckBuilder()
{
    int maxNumberOfCards = 40;
    int maxNumberOfHeroes = 6;
    int maxNumberOfEachCard = 3;
}

void addCard(Card &cardToAdd)
{
        Logger logger;
        
        if(cardCount[cardToAdd]=<3 || cardCount[cardToAdd] == NULL)
        {
            cardCount[cardToAdd]++;
            if (deck.numberOfCards >= 40)
            {
                logger.log("Nie można mieć więcej niż 40 kart \n", 0);
                break; //pozostałe karty nie zostają dodane
            }

            if (deck.numberOfHeroes >= 6 && cardToAdd.getSupertype() == "Hero") //example, have to check which value returns if its a hero or not
            {
                logger.log("Nie można mieć więcej niż 6 bohaterów \n",0);
                break;
            }

            // TO DO: checking if each card doesn't occur more than three times 

            if (deck.firstRegion == "")
            {
                deck.firstRegion = cardToAdd.getRegionRef();
            }
            else if (deck.secondRegion == "")
            {
                deck.secondRegion = cardToAdd.getRegionRef();
            }
            else
            {
                std::cout << "Nie można mieć kart z więcej niż dwóch regionów \n";
                break; //pozostałe karty nie zostają dodane
            }

            deck.deck.push_back(cardToAdd);
            numberOfCards++;
          }
          
          else{
            logger.log("Nie można mieć więcej, niż 3 takie same karty", 0);
            break;
          }
}

void removeCard(Card &cardToRemove)
{
    deck.deck.push_back(cardToRemove);
    deck.deck.pop_back();
    numberOfCards--;
  //  Sprawdzanie regionu każdej karty w decku
}

DeckBuilder::~DeckBuilder() {}
