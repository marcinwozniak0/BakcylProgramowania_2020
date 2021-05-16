#include <iostream>

#include "DeckWindow.h"
#include "ui_deckwindow.h"

const size_t deckWindowWidth = 890;
const size_t deckWindowHeight = 525;

DeckWindow::DeckWindow(DeckBuilder* deck, QRect geometry, SqliteHelper::unique_sqlite3* dataBase, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeckWindow),
    deck_(deck),
    dataBase_(dataBase)
{
    ui->setupUi(this);
    setGeometry(geometry);
    setFixedSize(deckWindowWidth, deckWindowHeight);
    CheckDeckFullfillment();
    CreateTypesChart();
    CheckDeckStats();
    CreateDeckDysplay();

    if(deck->getDeck().getCardsAsVector().size() > 0){
        currentCard_ = deck->getDeck().getCardsAsVector().at(0);
    }

    ConnectCard();

}
void DeckWindow::CreateTypesChart()
{
    CardsTypes types;

    CheckCardsTypes(types);

    series_ = new QPieSeries();
    series_->setVisible(false);
    series_->setPieSize(0.5);
    series_->setHoleSize(0.2);

    size_t graphSize = CreateGraph(types);

    for(size_t i = 0; i < graphSize; i++)
    {
        QPieSlice* slice = series_->slices().at(i);
        slice->setLabelVisible(true);
        slice->setBorderWidth(0);
        slice->setBorderColor(Qt::transparent);
        slice->setBrush(QColor(0,100,((i+130)*70)%256));
        slice->setLabelColor(Qt::gray);
    }
    //series->slices().at(selected)->setExploded(true);

    chart_ = new QChart();
    chart_->addSeries(series_);
    chart_->setBackgroundVisible(false);
    chartview_ = new QChartView(chart_, ui->Statystyki);
    chartview_->setGeometry(270, -50, 400, 300);

}

void DeckWindow::ConnectCard()
{
    for (auto& it : cardInDeckAsButtons_)
    {
        connect(it.get(), &QPushButton::clicked, this, &DeckWindow::cardClicked);
    }

}

void DeckWindow::CheckCardsTypes(CardsTypes& types)
{
    for(const auto& card : deck_->getDeck().getCardsAsVector())
    {
        switch(card.type[0])
        {
            case 'J': // "Jednostka"
                types.units++;
                break;

            case 'U': // "Umiejętność"
                types.skills++;
                break;

            case 'Z': // "Zaklęcie"
                types.spells++;
                break;

            case 'L': // "Lokacja"
                types.landmarks++;
                break;
        }
    }
}

size_t DeckWindow::CreateGraph(CardsTypes& types)
{
    size_t size {};
    if(types.units > 0)
    {
        series_->append(QString::fromStdString("Units: "+std::to_string(types.units)), types.units);
        size++;
    }
    if(types.skills > 0)
    {
        series_->append(QString::fromStdString("Skills: "+std::to_string(types.skills)), types.skills);
        size++;
    }
    if(types.spells > 0)
    {
        series_->append(QString::fromStdString("Spells: "+std::to_string(types.spells)), types.spells);
        size++;
    }
    if(types.landmarks > 0)
    {
        series_->append(QString::fromStdString("Landmarks: "+std::to_string(types.landmarks)), types.landmarks);
        size++;
    }
    return size;
}

void DeckWindow::CheckDeckStats()
{

    ui->Statystyki->findChild<QLabel*>("Region1")->setText(QString::fromStdString(deck_->firstRegion.name));
    ui->Statystyki->findChild<QLabel*>("Region2")->setText(QString::fromStdString(deck_->secondRegion.name));
    double healthsum = 0;
    double costsum = 0;
    double attacksum = 0;
    const int decksize = deck_->getDeck().getCardsAsVector().size();
    for(const auto& card : deck_->getDeck().getCardsAsVector())
    {
        healthsum+=card.health;
        costsum+=card.cost;
        attacksum+=card.attack;
    }
    ui->Statystyki->findChild<QLabel*>("Health")->setText(QString::number(healthsum/decksize));
    ui->Statystyki->findChild<QLabel*>("Cost")->setText(QString::number(costsum/decksize));
    ui->Statystyki->findChild<QLabel*>("Attack")->setText(QString::number(attacksum/decksize));
}

void DeckWindow::CheckDeckFullfillment()
{
    ui->deckFill->setValue(deck_->getDeckLength());

}

void DeckWindow::CreateDeckDysplay()
{

    scrollArea = std::make_unique<QScrollArea>(this);
    scrollArea->setWidget(ui->CardsInDeck);
    scrollArea->setGeometry(10,230,340,290);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ShowDeckDysplay();

}
void DeckWindow::ShowDeckDysplay()
{
    QRect positionAndSize {5,5,300,20};

    int heigth = 30;

    for(const auto& [key, value] : deck_->getCardCountMap())
    {
        std::shared_ptr button = std::make_shared<QPushButton>(ui->CardsInDeck);
        button->setText(QString::number(value) + "x " + QString::fromStdString(key.name));
        button->setGeometry(positionAndSize);
        button->setProperty("Id", QString::fromStdString(key.cardCode));
        positionAndSize.moveTop(heigth);
        heigth += 25;
        cardInDeckAsButtons_.push_back(button);
    }
    ui->CardsInDeck->setGeometry(10,230,340, heigth < 290 ? 286 : heigth - 25);
    cardInDeckAsButtons_.shrink_to_fit();
}


void DeckWindow::cardClicked()
{
    QPushButton *button = (QPushButton *)sender();
    currentCard_ = (CardApi::getCardById(*dataBase_, button->property("Id").toString().toStdString())).value();
}
void DeckWindow::on_Back_B_clicked()
{
    close();
}
void DeckWindow::on_ResetDeck_B_clicked()
{
    deck_->resetDeck();
    ShowDeckDysplay();
    cardInDeckAsButtons_.clear();

}

DeckWindow::~DeckWindow()
{
    delete chart_;
    delete ui;
}

