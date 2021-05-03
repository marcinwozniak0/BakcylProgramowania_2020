#include "deckwindow.h"
#include "ui_deckwindow.h"

DeckWindow::DeckWindow(DeckBuilder* deck ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeckWindow)
{
    ui->setupUi(this);
}

DeckWindow::~DeckWindow()
{
    delete ui;
}
