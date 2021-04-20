#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>

#include "cardwindow.h"

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

private slots:

    void on_Search_B_clicked();
    void on_Health_B_clicked();
    void on_Cost_B_clicked();
    void on_Attack_B_clicked();
    void on_Type_B_clicked();
    void on_Rarity_B_clicked();
    void on_Region_B_clicked();
    void cardClicked();
    void displayCardWindow(unsigned int cardId, QWidget *parent);

};
#endif // MAINWINDOW_H
