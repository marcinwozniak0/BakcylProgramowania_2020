#pragma once

#include <QDialog>
#include <QtCharts>
#include <memory>

#include "DeckBuilder.hpp"

namespace Ui {
class DeckWindow;
}

class DeckWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DeckWindow( DeckBuilder* deck, QRect geometry, QWidget *parent = nullptr);
    ~DeckWindow();

private:
    Ui::DeckWindow *ui;
    void CheckDeckFullfilment();
    void CreateTypesChart();
    void CheckDeckStats();
    DeckBuilder* deck_;

    QPieSeries* series;
    QChart* chart;
    QChartView* chartview;
};


