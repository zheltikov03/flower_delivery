#include "orderlist.h"
#include "ui_orderlist.h"

#include <QTime>
#include <QtAlgorithms>

#include "database.h"
#include "authorization.h"
#include "makingorder.h"
#include "orderinformation.h"

bool orderComp(order a, order b) {
    return a.getDateTime() < b.getDateTime();
}

orderList::orderList(user* User, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::orderList)
{
    ui->setupUi(this);
    this->User = User;
    if(User->getStatus() != 0)
        ui->newOrderButton->hide();
    ui->namelabel->setText(User->getName());
    reload();
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(reload()));
    timer->start(5000);
}

orderList::~orderList()
{
    timer->stop();
    delete ui;
}

void orderList::reload(){
    order Order;

    int selected = ui->ordersList->currentRow();
    if(selected != -1){
        Order = orders->at(selected);
        selected = Order.getId();
        if(!ui->ordersList->currentItem()->isSelected())
            selected = -1;
    }
    if(orders != NULL){
        delete orders;
    }

    ui->ordersList->clear();
    database base;
    orders = base.getOrders(User);

    std::sort(orders->begin(), orders->end(), orderComp);
    QString inscription;
    QString statuses[] = {"Подан", "Отменён", "Отклонен", "Сборка", "Ожидает курьера", "Доставка", "Завершен"};
    for( int i = 0; i < orders->size(); i++){
        Order = orders->at(i);
        inscription = "Заказ номер " +  QString::number(Order.getId())  + ": " + statuses[Order.getStatus()];
        ui->ordersList->addItem(inscription);
        inscription = "";
        if(Order.getId() == selected)
            ui->ordersList->setCurrentRow(i);
    }
}

void orderList::makingOrderWindow(){
    makingorder makingOrderWindow(User);
    makingOrderWindow.setModal(true);
    makingOrderWindow.exec();
    reload();
}

void orderList::orderInformationWindow(){
    order Order;
    int selected = ui->ordersList->currentRow();
    if(selected == -1)
        return;
    if(!ui->ordersList->currentItem()->isSelected())
        return;
    Order = orders->at(selected);

    orderinformation orderinformationWindow(User, orders->at(selected));
    orderinformationWindow.setModal(true);
    orderinformationWindow.exec();
    reload();
}

void orderList::logOut(){
    timer->stop();
    delete orders;
    delete User;
    authorization* auth = new authorization;
    auth ->show();
    this->close();
    delete this;
}
