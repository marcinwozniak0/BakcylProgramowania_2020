#ifndef CARDWINDOW_H
#define CARDWINDOW_H

#include <QDialog>

#include "DeckBuilder/Include/Card.hpp"

namespace Ui {
class CardWindow;
}

class CardWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CardWindow(QWidget *parent = nullptr);
     CardWindow(Card card, QWidget *parent = nullptr);
    ~CardWindow();

private:
    Ui::CardWindow *ui;
    Card card_;

private slots:
    void on_close_w_clicked();
};

#endif // CARDWINDOW_H
