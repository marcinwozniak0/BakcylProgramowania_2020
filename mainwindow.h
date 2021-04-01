#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <memory>


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
    std::unique_ptr<Ui::MainWindow> ui;
    void DisplayCards();

private slots:
    void on_Atak_B_clicked();
    void on_Typ_B_clicked();
    void on_Szukaj_B_clicked();

};
#endif // MAINWINDOW_H
