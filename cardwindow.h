#pragma once

#include <QDialog>

#include "DeckBuilder/Card.hpp"

namespace Ui {
class CardWindow;
}

class CardWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CardWindow(QWidget *parent = nullptr);
     CardWindow(unsigned int cardId, QWidget *parent = nullptr);
    ~CardWindow();

private:
    Ui::CardWindow *ui;
    unsigned int cardId_;

private slots:
    void on_close_w_clicked();
};


