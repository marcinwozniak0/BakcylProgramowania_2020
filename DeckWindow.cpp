#include "DeckWindow.h"
#include "ui_deckwindow.h"

const size_t deckWindowWidth = 890;
const size_t deckWindowHeight = 525;

DeckWindow::DeckWindow(DeckBuilder* deck, QRect geometry, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeckWindow),
    deck_(deck)
{
    ui->setupUi(this);
    setGeometry(geometry);
    setFixedSize(deckWindowWidth, deckWindowHeight);
    CheckDeckFullfillment();
    CreateTypesChart();
    CheckDeckStats();

}
void DeckWindow::CreateTypesChart()
{

    series = new QPieSeries();
    series->setVisible(false);
    series->append(" ",0);
    series->append("Bohaterowie",40);
    series->append("Specjalne",40);
    series->append("Spell",69);


    for (int i = 1; i < 4; i++) {
        QPieSlice *slice = series->slices().at(i);
        slice->setLabelVisible(true);
        slice->setPen(QPen(Qt::black));
        slice->setBrush(QColor((i*100)%255,(i*100)%255,(i*100)%255));
        slice->setLabelColor(Qt::white);
    }
    chart = new QChart();
    chart->addSeries(series);
    chart->setBackgroundVisible(false);
    chartview = new QChartView(chart, ui->Statystyki);
    chartview->setGeometry(300, 0, 350, 200);

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

DeckWindow::~DeckWindow()
{
    delete chart;
    delete ui;
}


void DeckWindow::CheckDeckFullfillment(){
    ui->deckFill->setValue(deck_->getDeckLength());

}
