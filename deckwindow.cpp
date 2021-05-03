#include "deckwindow.h"
#include "ui_deckwindow.h"

DeckWindow::DeckWindow(DeckBuilder* deck, QRect geometry ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeckWindow),
    deck_(deck)
{
    ui->setupUi(this);
    setGeometry(geometry);
    setFixedSize(geometry.width(), geometry.height());
    CheckDeckFullfilment();
}

DeckWindow::~DeckWindow()
{
    delete ui;
}

void DeckWindow::CheckDeckFullfilment(){

    ui->deckFill->setValue(50);
}
