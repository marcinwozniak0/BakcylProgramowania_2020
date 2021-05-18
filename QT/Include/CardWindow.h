#pragma once

#include <QDialog>
#include <QPlainTextEdit>


#include "DeckBuilder.hpp"


namespace Ui {
class CardWindow;
}

class CardWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CardWindow(QWidget *parent = nullptr);
     CardWindow(std::string cardId, QPlainTextEdit* DeckDisplay, DeckBuilder* deck, SqliteHelper::unique_sqlite3* DataBase, QWidget *parent = nullptr);
    ~CardWindow();

private:
    Ui::CardWindow *ui;
    std::string cardId_;
    QPlainTextEdit* DeckDisplay_;
    DeckBuilder* deck_;
    std::string deckText_;
    SqliteHelper::unique_sqlite3* DataBase_;

    void displayDeck();

private slots:
    void on_close_w_clicked();
    void on_add_w_clicked();
};


