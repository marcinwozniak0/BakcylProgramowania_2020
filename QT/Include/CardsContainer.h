#pragma once

#include <vector>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>


class CardsContainer : public QWidget
{
    Q_OBJECT
public:
    explicit CardsContainer(QWidget* parent = nullptr);
    ~CardsContainer();
    std::vector<QPushButton*> getCards(){return cards_;}
    void displayCards(std::vector<std::string> cardsCodes);

private:
    void createLayout(QWidget *parent);    
    void showCard(QString path, QPushButton* button);

    std::vector<QPushButton*> cards_;

    QPushButton *m_button;
    QWidget* parent_;



};

