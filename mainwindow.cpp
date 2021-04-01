#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
#include <QRegularExpression>
#include <QMessageBox>

#include "searchrequest.h"

void CenterWindow(QWidget *widget);
void showCard(QString path, QLabel* label);

constexpr size_t windowWight = 1200; //px
constexpr size_t windowHeight = 800; //px

void CenterWindow(QWidget *widget);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //ui->groupBox_2->setStyleSheet("QFrame{border:0px solid black}");//Hide a card borders

    DisplayCards();
    setFixedSize(windowWight,windowHeight);

    setFixedSize(windowWight,windowHeight);
    CenterWindow(this);


}
MainWindow::~MainWindow()
{
}


void MainWindow::on_Szukaj_B_clicked(){
    std::bitset<4> type;
    type.set(1,true);
      int zdrowie_od=ui->Zdrowie_od->text().toInt();
      int zdrowie_do=ui->Zdrowie_do->text().toInt();
      int zdrowie_value=ui->Zdrowie_value->text().toInt();
      int koszt_od=ui->Koszt_od->text().toInt();
      int koszt_do=ui->Koszt_do->text().toInt();
      int koszt_value=ui->Koszt_value->text().toInt();
      int atak_od=ui->Atak_od->text().toInt();
      int atak_do=ui->Atak_do->text().toInt();
      int atak_value=ui->Atak_value->text().toInt();
//    (ui->Typ->findChildren<QCheckBox*>("Typ_1",Qt::FindChildrenRecursively));
    SearchRequest request(zdrowie_od,zdrowie_do,zdrowie_value,
                          koszt_od,koszt_do,koszt_value,
                          atak_od,atak_do,atak_value,
                          ui->Nazwa_T->text().toStdString(),
                          000,/*typ*/ 0000,000'000'000'000'0);
//                          ui->Koszt_od->text().toInt(),
//                          ui->Koszt_do->text().toInt(),
//                          ui->Koszt_value->text().toInt(),





    request.ShowRequest();
}
void MainWindow::DisplayCards(){
        QRegularExpression label_regex("label_pic??");
        auto childrens = ui->groupBox_2->findChildren<QLabel*>(label_regex);
        for(auto& it : childrens){
            showCard("../../BakcylProgramowania_2020/source/pic.png",it); //TODO: Zmienić tego statycznego stringa na listę zdjęć i iterować po zdjęciach a nie po label
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



void MainWindow::on_Zdrowie_B_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_Koszt_B_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_Atak_B_clicked()
{
     ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_Typ_B_clicked()
{
     ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_Rzadkosc_B_clicked()
{
     ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_Region_B_clicked()
{
     ui->stackedWidget->setCurrentIndex(6);
}
