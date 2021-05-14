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
    int units = 0;
    int skills = 0;
    int spells = 0;
    int landmarks = 0;
 /* Pierwszy pomysł na zdobycie ilości typów. Niestety wszystkie typy kart na ten moment nazywają się "type" :p
    for(const auto& card : deck_->getDeck().getCardsAsVector())
    {
        switch(card.type[0])
        {
            case 'J': // "Jednostka"
                units++;
                break;

            case 'U': // "Umiejętność"
                skills++;
                break;

            case 'Z': // "Zaklęcie"
                spells++;
                break;

            case 'L': // "Lokacja"
                landmarks++;
                break;
        }
    }

*/

    series = new QPieSeries();
    series->setVisible(false);
    series->setPieSize(0.5);
    series->setHoleSize(0.2);

int piesize = 0;
if(units > 0)
{
    series->append(QString::fromStdString("Units: "+std::to_string(units)),units);
    piesize++;
}
if(skills > 0)
{
    series->append(QString::fromStdString("Skills: "+std::to_string(skills)),skills);
    piesize++;
}
if(spells > 0)
{
    series->append(QString::fromStdString("Spells: "+std::to_string(spells)),spells);
    piesize++;
}
if(landmarks > 0)
{
    series->append(QString::fromStdString("Landmarks: "+std::to_string(landmarks)),landmarks);
    piesize++;
}
for (int i = 0; i < piesize; i++) {
        QPieSlice* slice = series->slices().at(i);
        slice->setLabelVisible(true);
        slice->setBorderWidth(0);
        slice->setBorderColor(Qt::transparent);
        slice->setBrush(QColor(0,100,((i+130)*70)%256));
        slice->setLabelColor(Qt::gray);
    }
    //series->slices().at(selected)->setExploded(true);


    chart = new QChart();
    chart->addSeries(series);
    chart->setBackgroundVisible(false);
    chartview = new QChartView(chart, ui->Statystyki);
    chartview->setGeometry(270, -50, 400, 300);

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
