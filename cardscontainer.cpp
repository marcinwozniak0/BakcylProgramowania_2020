#include "cardscontainer.h"

CardsContainer::CardsContainer(QWidget *parent) : QWidget(parent)
{
    for(auto& it : cardButton)
    {
        it = new cardButton(id, this);
        connect(it, SIGNAL(clicked(int)), this, SIGNAL(digitClicked(int)));

    }
    createLayout();

}

void CardsContainer::createLayout()
{
    QGridLayout* layout = new QGridLayout(this);


}


