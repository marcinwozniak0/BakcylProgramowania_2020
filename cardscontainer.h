#ifndef CARDSCONTAINER_H
#define CARDSCONTAINER_H

#include <QWidget>
#include <QGridLayout>

class CardsContainer : public QWidget
{
    Q_OBJECT
public:
    explicit CardsContainer(QWidget *parent = nullptr);

private:
    void createLayout();

};

#endif // CARDSCONTAINER_H
