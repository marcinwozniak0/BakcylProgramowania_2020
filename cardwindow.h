#ifndef CARDWINDOW_H
#define CARDWINDOW_H

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
    explicit CardWindow(Card card, QWidget *parent = nullptr);
    ~CardWindow();

private:
    Ui::CardWindow *ui;
};

#endif // CARDWINDOW_H
