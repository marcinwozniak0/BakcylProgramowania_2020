#pragma once

#include <QDialog>
#include <QtCharts>
#include <memory>

#include "DeckBuilder/Include/DeckBuilder.hpp"

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
    DeckBuilder* deck_;
    std::unique_ptr<QPieSeries> series;
    std::unique_ptr<QChart> chart;
    std::unique_ptr<QChartView> chartview;
};


