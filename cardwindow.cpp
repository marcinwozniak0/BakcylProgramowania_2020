#include "cardwindow.h"
#include "ui_cardwindow.h"

CardWindow::CardWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CardWindow)
{
    ui->setupUi(this);
}
CardWindow::CardWindow(Card card, QWidget *parent){

}
CardWindow::~CardWindow()
{
    delete ui;
}
