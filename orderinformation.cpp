#include "orderinformation.h"
#include "ui_orderinformation.h"

#include <QMessageBox>

#include "database.h"

orderinformation::orderinformation(user* User, order Order, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::orderinformation)
{
    ui->setupUi(this);
    this->User = User;
    this->Order = Order;

    activateButtons();
    hideButtons();

    database base;
    bouquet Bouquet = base.getBouquets()->at(Order.getBouquetID());
    QString statuses[] = {"Подан", "Отменён", "Отклонен", "Сборка", "Ожидает курьера", "Доставка", "Завершен"};

    ui->nameLabel->setText(ui->nameLabel->text() + base.getUser(Order.getUserID())->getName());
    ui->phoneLabel->setText(ui->phoneLabel->text() + base.getUser(Order.getUserID())->getPhone());
    ui->addressLabel->setText(ui->addressLabel->text() + Order.getAddress());
    ui->dateLabel->setText(ui->dateLabel->text() + QDateTime::fromSecsSinceEpoch(Order.getDateTime()).date().toString("d.M.yyyy"));
    ui->timeLabel->setText(ui->timeLabel->text() + QDateTime::fromSecsSinceEpoch(Order.getDateTime()).time().toString("h:mm"));
    ui->bouquetLabel->setText(ui->bouquetLabel->text() + Bouquet.getName());
    ui->priceLabel->setText(ui->priceLabel->text() + QString::number(Bouquet.getPrice()) + "р.");
    ui->statusLabel->setText(ui->statusLabel->text() + statuses[Order.getStatus()]);
    ui->dopInfoLabel->setText(ui->dopInfoLabel->text() + Order.getDopInfo());
}

orderinformation::~orderinformation()
{
    delete ui;
}

void orderinformation::activateButtons(){
    switch (Order.getStatus()) {
    case 0:
        ui->cancelButton->setEnabled(true);
        ui->rejectButton->setEnabled(true);
        ui->workFloristButton->setEnabled(true);
        break;
    case 3:
        ui->completeFloristButton->setEnabled(true);
        break;
    case 4:
        ui->workCourierButton->setEnabled(true);
        break;
    case 5:
        ui->completeCourierButton->setEnabled(true);
        break;
    }
}

void orderinformation::hideButtons(){
    switch (User->getStatus()) {
    case 0:
        ui->rejectButton->hide();
        ui->workFloristButton->hide();
        ui->completeFloristButton->hide();
        ui->workCourierButton->hide();
        ui->completeCourierButton->hide();
        break;
    case 1:
        ui->cancelButton->hide();
        ui->workCourierButton->hide();
        ui->completeCourierButton->hide();
        break;
    case 2:
        ui->cancelButton->hide();
        ui->rejectButton->hide();
        ui->workFloristButton->hide();
        ui->completeFloristButton->hide();
        break;
    }
}

void orderinformation::cancelOrder(){
    changeStatus(1, "Заказ успешко отменён.");
}

void orderinformation::rejectOrder(){
    changeStatus(2, "Заказ успешко отклонён.");
}

void orderinformation::workFlorist(){
    changeStatus(3, "Вы приступили к заказу.");
}

void orderinformation::completeFlorist(){
    changeStatus(4, "Вы завершили заказ.");
}

void orderinformation::workCourier(){
    changeStatus(5, "Вы приступили к доставке.");
}

void orderinformation::completeCourier(){
    changeStatus(6, "Вы завершили доставку.");
}

void orderinformation::changeStatus(int newStatus, QString message){
    database base;
    if(base.changeOrderStatus(Order.getId(), newStatus, User->getId())){
        QMessageBox::information(this, "Статус изменён", message);
        this->close();
    }
    else
        QMessageBox::critical(this, "Ошибка","Ошибка смены статуса заказа!\n Возможно, статус заказа уже был изменён.");
}
