#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
#include <QRegularExpression>
#include <iostream>

#include "cardscontainer.h"
#include "searchrequest.h"


constexpr size_t windowWight = 1200; //px
constexpr size_t windowHeight = 800; //px

void centerWindow(QWidget *widget);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);
    setFixedSize(windowWight,windowHeight);
    setFixedSize(windowWight,windowHeight);
    centerWindow(this);
    this->setWindowTitle("Deckbuilder");

    CardsContainer cardContainer(ui->groupBox_2);
    for(auto& it : cardContainer.getCards()){
        connect(it, &QPushButton::clicked, this, &MainWindow::cardClicked);
    }

}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Search_B_clicked(){

    SearchRequest request(ui->Health_from->text().toStdString(),
                          ui->Health_to->text().toStdString(),

                          ui->Cost_from->text().toStdString(),
                          ui->Cost_to->text().toStdString(),


                          ui->Attack_from->text().toStdString(),
                          ui->Attack_to->text().toStdString(),

                          ui->Name_T->text().toStdString(),
                          convertCheckbox("Rarity_?"),
                          convertCheckbox("Typ_?"),
                          convertCheckbox("Region_??"));

    request.ShowRequest();

}
std::vector<std::string> MainWindow::convertCheckbox(std::string regex){
    QRegularExpression chexbox_regex(regex.c_str());
    std::vector<std::string> checkboxNames;

    for(auto& it : ui->groupBox_3->findChildren<QCheckBox*>(chexbox_regex)){
        if(it->isChecked()){
                checkboxNames.push_back(it->text().toUtf8().constData());
        }
    }
    return checkboxNames;
}
void MainWindow::cardClicked(){
    QPushButton *button = (QPushButton *)sender();
    emit displayCardWindow(button->property("Id").toUInt());

}
void MainWindow::displayCardWindow(unsigned int id){
    CardWindow cardW(id,ui->groupBox_3->findChild<QLabel*>("DeckDisplay"), &deckbuilder, this);
    cardW.setModal(true);
    cardW.exec();
}

void centerWindow(QWidget *widget){

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



void MainWindow::on_Health_B_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_Cost_B_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_Attack_B_clicked()
{
     ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_Type_B_clicked()
{
     ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_Rarity_B_clicked()
{
     ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_Region_B_clicked()
{
     ui->stackedWidget->setCurrentIndex(6);
}

