#pragma once

#include <QDialog>
#include <QtCharts>
#include <memory>
#include <vector>

#include "DeckBuilder.hpp"

struct CardsTypes
{
    size_t units {};
    size_t skills {};
    size_t spells {};
    size_t landmarks {};
};

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
    void CheckDeckFullfillment();
    void CreateTypesChart();
    void CheckDeckStats();
    void CheckCardsTypes(CardsTypes& types);
    void CreateDeckDysplay();
    size_t CreateGraph(CardsTypes&);

    DeckBuilder* deck_;

    std::vector<QPushButton*> cardInDeckAsButtons;
    QPieSeries* series;
    QChart* chart;
    QChartView* chartview;
};


