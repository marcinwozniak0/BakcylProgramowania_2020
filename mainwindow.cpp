#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
#include <QRegularExpression>

#include "searchrequest.h"

void CenterWindow(QWidget *widget);
void showCard(QString path, QPushButton* button);

constexpr size_t windowWight = 1200; //px
constexpr size_t windowHeight = 800; //px

void CenterWindow(QWidget *widget);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    ui->stackedWidget->setCurrentIndex(0);
    DisplayCards();
    setFixedSize(windowWight,windowHeight);

    setFixedSize(windowWight,windowHeight);
    CenterWindow(this);


}
MainWindow::~MainWindow()
{
}


void MainWindow::on_Szukaj_B_clicked(){

    QRegularExpression rarity_regex("Rarity_?");
    auto rarity = ui->Rzadkosc->findChildren<QCheckBox*>(rarity_regex);
    QRegularExpression type_regex("Typ_?");
    auto type = ui->Typ->findChildren<QCheckBox*>(type_regex);
    QRegularExpression region_regex("Region_??");
    auto regions = ui->Region->findChildren<QCheckBox*>(region_regex);

    SearchRequest request(ui->Zdrowie_od->text().toInt(),
                          ui->Zdrowie_do->text().toInt(),
                          ui->Zdrowie_value->text().toInt(),

                          ui->Koszt_od->text().toInt(),
                          ui->Koszt_do->text().toInt(),
                          ui->Koszt_value->text().toInt(),

                          ui->Atak_od->text().toInt(),
                          ui->Atak_do->text().toInt(),
                          ui->Atak_value->text().toInt(),
                          ui->Nazwa_T->text().toStdString(),
                          rarity,
                          type,
                          regions);

    request.ShowRequest();
    //TODO: Ustalić kolejność i znaczenie poszczególnych bitów w typie, rzadkości i regionach
}
void MainWindow::DisplayCards(){
        QRegularExpression pic_regex("button_pic??");
        auto childrensPic = ui->groupBox_2->findChildren<QPushButton*>(pic_regex);
        for(auto& it : childrensPic){
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

void showCard(QString path, QPushButton* button){
    QPixmap picture(path);
    QIcon buttonIcon(picture);
    button->setIcon(buttonIcon);
    button->setIconSize(button->rect().size());
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
