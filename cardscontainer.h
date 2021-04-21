#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>


class CardsContainer : public QWidget
{
    Q_OBJECT
public:
    explicit CardsContainer(QWidget* parent = nullptr);

    std::vector<QPushButton*> getCards(){return cards_;}
    void displayCardWindow([[maybe_unused]] size_t id, QWidget* parent);

private:
    void createLayout(QWidget *parent);
    void displayCards();
    void showCard(QString path, QPushButton* button);


    std::vector<QPushButton*> cards_;


    QPushButton *m_button;
    QWidget* parent_;



};

