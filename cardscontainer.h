#ifndef CARDSCONTAINER_H
#define CARDSCONTAINER_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>


class CardsContainer : public QWidget
{
    Q_OBJECT
public:
    explicit CardsContainer(QWidget *parent = nullptr);

private:
    void createLayout();
    void displayCards();

    void showCard(QString path, QPushButton* button);

    std::vector<QPushButton*> cards_;


};

#endif // CARDSCONTAINER_H
