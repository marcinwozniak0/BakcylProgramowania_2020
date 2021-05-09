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
    CreateTypesChart();

}
void DeckWindow::CreateTypesChart()
{

    series = std::make_unique<QPieSeries>();
    series->append("Test",10);
    series->append("Lol",40);
    series->append("xD",69);
    chart = std::make_unique<QChart>();
    chart->addSeries(series.get());
    // TODO
    //chart->setBackgroundVisible(true);
    //chart->setTheme(QChart::C);
    chartview = std::make_unique<QChartView>(chart.get(), ui->Statystyki);
    chartview->setGeometry(300, 10, 300, 200);

}
DeckWindow::~DeckWindow()
{
    delete ui;
}

void DeckWindow::CheckDeckFullfilment(){
    ui->deckFill->setValue(deck_->getDeckLength());
}
