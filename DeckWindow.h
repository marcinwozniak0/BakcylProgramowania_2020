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
    explicit DeckWindow(DeckBuilder* deck, QRect geometry, SqliteHelper::unique_sqlite3* dataBase, QWidget *parent = nullptr);
    ~DeckWindow();

private:
    Ui::DeckWindow *ui;
    void CheckDeckFullfillment();
    void CreateTypesChart();
    void CheckDeckStats();
    void CheckCardsTypes(CardsTypes& types);
    void CreateDeckDysplay();
    void ConnectCard();
    void ShowDeckDysplay();
    size_t CreateGraph(CardsTypes&);

    DeckBuilder* deck_;
    CardApi::Card currentCard_;
    SqliteHelper::unique_sqlite3* dataBase_;
    std::unique_ptr<QScrollArea> scrollArea;
    std::vector<std::shared_ptr<QPushButton>> cardInDeckAsButtons_;
    QPieSeries* series_;
    QChart* chart_;
    QChartView* chartview_;
private slots:
    void cardClicked();
    void on_Back_B_clicked();
    void on_ResetDeck_B_clicked();
};


