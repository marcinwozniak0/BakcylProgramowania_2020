#include "cardscontainer.h"

#include <QVariant>
#include <iostream>

CardsContainer::CardsContainer(QWidget* parent) :
    QWidget(parent),
    parent_(parent)
{

    createLayout(parent_);

    displayCards();
}

void CardsContainer::displayCards(){

        int i = 0;
        for(auto& it : cards_){
            showCard("../../BakcylProgramowania_2020/source/pic.png",it); //TODO: Zmienić tego statycznego stringa na listę zdjęć i iterować po zdjęciach a nie po buttonach
            it->setProperty("Id", i);                                     //TODO: ID powinno być id karty
            i++;
        }
}

void CardsContainer::createLayout(QWidget* parent)
{

    int posX = 90;
    int posY = 30;

    const size_t cardHeight = 160;
    const size_t cardWight = 120;

    const size_t maxCardsDisplay = 15;

    for(size_t i = 0; i < maxCardsDisplay; i++){

        cards_.push_back(new QPushButton(parent));
        cards_[i]->move(posX,posY);
        cards_[i]->setMinimumSize(cardWight,cardHeight);
        cards_[i]->setFlat(true);

        if((i+1)% 5 == 0){
            posY += cardHeight + 5; //margin top/bottom
            posX -= (cardWight + 30) * 4;
        }else{
            posX += cardWight + 30; //margin right/left
        }


   }

}

void CardsContainer::showCard(QString path, QPushButton* button){
    QPixmap picture(path);
    QIcon buttonIcon(picture);
    button->setIcon(buttonIcon);
    button->setIconSize(button->rect().size());
}
