#include "cardbutton.h"

CardButton::CardButton(int cardId, QWidget* parent)
    : QPushButton(parent)
{
    cardId_ = cardId;
    connect(this, SIGNAL(clicked()), this , SLOT(remmitClicked()));

}
void CardButton::remmitClicked()
{

    emit clicked(cardId_);
}
