#include "makingorder.h"
#include "ui_makingorder.h"

#include "database.h"

const QString makingorder::imagesFile = "D:/университет/курсовой проекс/bouquets/";

makingorder::makingorder(user* User, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::makingorder)
{
    ui->setupUi(this);
    this->User = User;
    database base;
    bouquets = base.getBouquets();
    if(bouquets->size() > 0){
        bouquetIndex = 0;
        bouquet Bouquet = bouquets->at(bouquetIndex);
        QPixmap pixmap;
        pixmap.load(imagesFile + QString::number(Bouquet.getId()) + ".jpg");
        ui->image->setPixmap(pixmap.scaled(170, 200, Qt::KeepAspectRatio));
        ui->bouquetNamePrice->setText(Bouquet.getName() + " " + QString::number(Bouquet.getPrice()) + "р");

        ui->dateEdit->setMinimumDate(QDate::currentDate().addDays(1));
        ui->previousButton->setDisabled(true);
        if(bouquetIndex == bouquets->size()-1)
            ui->nextButton->setDisabled(true);
    }
}

makingorder::~makingorder()
{
    delete ui;
}

void makingorder::nextBouquet(){
    bouquetIndex++;
    bouquet Bouquet = bouquets->at(bouquetIndex);
    QPixmap pixmap;
    pixmap.load(imagesFile + QString::number(Bouquet.getId()) + ".jpg");
    ui->image->setPixmap(pixmap.scaled(170, 200, Qt::KeepAspectRatio));
    ui->bouquetNamePrice->setText(Bouquet.getName() + " " + QString::number(Bouquet.getPrice()) + "р");

    ui->previousButton->setDisabled(false);
    if(bouquetIndex == bouquets->size()-1)
        ui->nextButton->setDisabled(true);
}

void makingorder::previousBouquet(){
    bouquetIndex--;
    bouquet Bouquet = bouquets->at(bouquetIndex);
    QPixmap pixmap;
    pixmap.load(imagesFile + QString::number(Bouquet.getId()) + ".jpg");
    ui->image->setPixmap(pixmap.scaled(170, 200, Qt::KeepAspectRatio));
    ui->bouquetNamePrice->setText(Bouquet.getName() + " " + QString::number(Bouquet.getPrice()) + "р");

    ui->nextButton->setDisabled(false);
    if(bouquetIndex == 0)
        ui->previousButton->setDisabled(true);
}

void makingorder::makeOrder(){
    QDateTime dateTime;
    dateTime.setDate(ui->dateEdit->date());
    dateTime.setTime(QTime::fromString(ui->timeEdit->currentText(), "h:mm"));

    newOrder.setUserID(User->getId());
    newOrder.setBouquetID(bouquetIndex);
    newOrder.setFloristID(-1);
    newOrder.setCourierID(-1);
    newOrder.setStatus(0);
    newOrder.setAddress(ui->addressLine->text());
    newOrder.setDateTime(dateTime.toSecsSinceEpoch());
    newOrder.setDopInfo(ui->dopInfoEdit->toPlainText());

    database base;
    base.newOrder(newOrder);

    this->close();
}
