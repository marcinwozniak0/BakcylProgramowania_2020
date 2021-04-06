#include "cardwindow.h"
#include "ui_cardwindow.h"

CardWindow::CardWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CardWindow)
{
    ui->setupUi(this);
}
CardWindow::CardWindow(Card card, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CardWindow),
    card_(card)
{
     ui->setupUi(this);
    QPixmap picture("../../BakcylProgramowania_2020/source/pic.png");
    int wp = ui->label->width();
    int hp = ui->label->height();
    ui->label->setPixmap(picture.scaled(wp,hp,Qt::KeepAspectRatio));

}
CardWindow::~CardWindow()
{
    delete ui;
}
