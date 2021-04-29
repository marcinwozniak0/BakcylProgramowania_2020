#pragma once

#include <QDesktopWidget>
#include <QMainWindow>

#include "cardscontainer.h"
#include "cardwindow.h"
#include "DeckBuilder/Include/DeckBuilder.hpp"
#include "searchrequest.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;

    void createCards();
    void displayCards();

    std::vector<std::string> convertCheckbox(std::string);
    CardsContainer* cardContainer;
    DeckBuilder deckbuilder;
    SearchRequest* currentRequest;


private slots:

    void on_Search_B_clicked();
    void on_Health_B_clicked();
    void on_Cost_B_clicked();
    void on_Attack_B_clicked();
    void on_Type_B_clicked();
    void on_Rarity_B_clicked();
    void on_Region_B_clicked();
    void cardClicked();
    void displayCardWindow(unsigned int cardId);

    void on_GoNext_B_clicked();
    void on_GoBack_B_clicked();

    void on_NumberOfPage_editingFinished();
};

