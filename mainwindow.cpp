#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <iostream>

void CenterWindow(QWidget *widget);
void showCard(QString path, QLabel *label);

constexpr size_t windowWight = 1200; //px
constexpr size_t windowHeight = 700; //px

void CenterWindow(QWidget *widget);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(std::make_unique<Ui::MainWindow>())
{
    ui->setupUi(this);

    showCard("../../BakcylProgramowania_2020/source/pic.png",ui->label_pic1);
    setFixedSize(windowWight,windowHeight);

    setFixedSize(windowWight,windowHeight);
    CenterWindow(this);


}
MainWindow::~MainWindow()
{
}

void MainWindow::on_Atak_B_clicked(){
    QMessageBox::information(this,"Title","Atack");
    ui->Szukaj_B->setText("Hi");


}


void CenterWindow(QWidget *widget){

    int x, y;
    int screenWidth;
    int screenHeight;

    QDesktopWidget *desktop = QApplication::desktop();

    screenWidth = desktop->width();
    screenHeight = desktop->height();


    x = (screenWidth - windowWight) / 2;
    y = (screenHeight - windowHeight) / 2;

    widget->setGeometry(x,y,windowWight,windowHeight);

}

void showCard(QString path, QLabel *label){
    QPixmap picture(path);
    int wp = label->width();
    int hp = label->height();
    label->setPixmap(picture.scaled(wp,hp,Qt::KeepAspectRatio));
}
