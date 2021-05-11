#include "DeckWindow.h"
#include "ui_deckwindow.h"

#include <iostream>
DeckWindow::DeckWindow(DeckBuilder* deck, QRect geometry, QWidget *parent) :
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

    series = new QPieSeries();
    series->setVisible(false);
    series->append(" ",0);
    series->append("Bochaterowie",40);
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
DeckWindow::~DeckWindow()
{
//    delete series;
//    delete chartview; // IDK jak to kosuję to apka crashuje. I <3 QT
    delete chart;
    delete ui;
}


void DeckWindow::CheckDeckFullfilment(){
    ui->deckFill->setValue(deck_->getDeckLength());

}
