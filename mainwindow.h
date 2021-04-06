#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>


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
    void DisplayCards();

private slots:

    void on_Szukaj_B_clicked();
    void on_Zdrowie_B_clicked();
    void on_Koszt_B_clicked();
    void on_Atak_B_clicked();
    void on_Typ_B_clicked();
    void on_Rzadkosc_B_clicked();
    void on_Region_B_clicked();

    void on_button_pic1_clicked();
};
#endif // MAINWINDOW_H
