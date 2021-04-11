#ifndef CARDBUTTON_H
#define CARDBUTTON_H
#include <QWidget>
#include <QPushButton>

class CardButton : public QPushButton
{
    Q_OBJECT
public:

    CardButton(int cardId, QWidget* parent);
signals:

    void clicked(int cardId);
private: slot:

    void remmitClicked();
private:

    int cardId_;

};

#endif // CARDBUTTON_H
