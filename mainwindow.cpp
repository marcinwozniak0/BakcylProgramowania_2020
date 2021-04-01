#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QRegularExpression>
#include <QMessageBox>
#include <iostream>

void CenterWindow(QWidget *widget);
void showCard(QString path, QLabel* label);

constexpr size_t windowWight = 1200; //px
constexpr size_t windowHeight = 800; //px

void CenterWindow(QWidget *widget);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(std::make_unique<Ui::MainWindow>())
{
    ui->setupUi(this);
    ui->ZKA_Opcje->hide();
    ui->Typ_Opcje->hide();

    ui->groupBox_2->setStyleSheet("QFrame{border:0px solid black}");//Hide a card borders

    DisplayCards();
    setFixedSize(windowWight,windowHeight);

    setFixedSize(windowWight,windowHeight);
    CenterWindow(this);


}
MainWindow::~MainWindow()
{
}

void MainWindow::on_Atak_B_clicked(){
    ui->ZKA_Opcje->show();
    ui->Typ_Opcje->hide();
}
void MainWindow::on_Typ_B_clicked(){
    ui->Typ_Opcje->show();
    ui->ZKA_Opcje->hide();
}
void MainWindow::DisplayCards(){
        QRegularExpression label_regex("label_pic??");
        auto childrens = ui->groupBox_2->findChildren<QLabel*>(label_regex);
        std::cerr<<childrens.length();
        for(auto& it : childrens){
            showCard("../../BakcylProgramowania_2020/source/pic.png",it);
        }

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

void showCard(QString path, QLabel* label){
    QPixmap picture(path);
    int wp = label->width();
    int hp = label->height();
    label->setPixmap(picture.scaled(wp,hp,Qt::KeepAspectRatio));
}
