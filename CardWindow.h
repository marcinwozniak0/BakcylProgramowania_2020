#pragma once

#include <QDialog>
#include <QLabel>


#include "DeckBuilder/Include/DeckBuilder.hpp"


namespace Ui {
class CardWindow;
}

class CardWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CardWindow(QWidget *parent = nullptr);
     CardWindow(unsigned int cardId, QLabel* DeckDisplay, DeckBuilder* deck ,QWidget *parent = nullptr);
    ~CardWindow();

private:
    Ui::CardWindow *ui;
    unsigned int cardId_;
    QLabel* DeckDisplay_;
    DeckBuilder* deck_;

private slots:
    void on_close_w_clicked();
    void on_add_w_clicked();
};


