#include "CardWindow.h"
#include "ui_cardwindow.h"

CardWindow::CardWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CardWindow)
{
    ui->setupUi(this);
}
CardWindow::CardWindow(std::string cardId, QLabel* DeckDisplay, DeckBuilder* deck, SqliteHelper::unique_sqlite3* DataBase, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CardWindow),
    cardId_(cardId),
    DeckDisplay_(DeckDisplay),
    deck_(deck),
    DataBase_(DataBase)
{
    ui->setupUi(this);
    QPixmap picture("../../BakcylProgramowania_2020/source/pic.png");
    int wp = ui->label->width();
    int hp = ui->label->height();
    ui->label->setPixmap(picture.scaled(wp,hp,Qt::KeepAspectRatio));
    this->setWindowTitle("Card");
}
CardWindow::~CardWindow()
{
    delete ui;
}

void CardWindow::on_close_w_clicked()
{
    close();
}

void CardWindow::on_add_w_clicked()
{
    deck_->addCardByID(*DataBase_, cardId_);
    displayDeck();
}

void CardWindow::displayDeck(){
    deckText_ = "";
    for(auto it : (deck_->getDeck()).getCardsAsVector()){
        deckText_ += it.name;
        deckText_ += '\n';
    }
    DeckDisplay_->setText(QString::fromStdString(deckText_));
}
