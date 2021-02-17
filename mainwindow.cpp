#include "mainwindow.h"
#include "./ui_mainwindow.h"

void CenterWindow(QWidget *widget);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(1200,700); //width, height in px

    CenterWindow(this);

}
MainWindow::~MainWindow()
{
    delete ui;
}

void CenterWindow(QWidget *widget){
    int x, y;
    int screenWidth;
    int screenHeight;

    QDesktopWidget *desktop = QApplication::desktop();

    screenWidth = desktop->width();
    screenHeight = desktop->height();

    x = (screenWidth - 1200) / 2;
    y = (screenHeight - 700) / 2;

    widget->setGeometry(x,y,1200,700);
}
