#include "makingorder.h"
#include "ui_makingorder.h"

#include <QStandardItemModel>

#include "database.h"
#include "order.h"

const QString makingorder::imagesFile = "D:/университет/курсовой проект/bouquets/";

makingorder::makingorder(user* User, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::makingorder)
{
    ui->setupUi(this);
    this->User = User;
    database base;
    bouquets = base.getBouquets();

    QStandardItemModel* model = new QStandardItemModel(ui->tableView);

    model->setHorizontalHeaderLabels(QStringList() << "id" << "Название" << "Цена");

    for (int row = 0; row < bouquets->count(); ++row) {
        QList<QStandardItem *> items;
        bouquet bouquet = bouquets->at(row);
        items.append(new QStandardItem(QString::number(row)));
        items.append(new QStandardItem(bouquet.getName()));
        items.append(new QStandardItem(QString::number(bouquet.getPrice())));
        model->appendRow(items);
    }

    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    QHeaderView* horizontalHeader = ui->tableView->horizontalHeader();
    horizontalHeader->setSectionResizeMode(QHeaderView::Stretch);

    ui->calendarWidget->setMinimumDate(QDate::currentDate().addDays(1));
}

makingorder::~makingorder()
{
    delete ui;
}

void makingorder::makeOrder(){
    QDateTime dateTime;
    dateTime.setDate(ui->calendarWidget->selectedDate());
    dateTime.setTime(QTime::fromString(ui->timeEdit->currentText(), "h:mm"));
    order newOrder;

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

void makingorder::selectBouquet(const QModelIndex &index)
{
    bouquetIndex = ui->tableView->model()->index(index.row(), 0).data().toInt();
    bouquet Bouquet = bouquets->at(bouquetIndex);
    QPixmap pixmap;
    pixmap.load(imagesFile + QString::number(Bouquet.getId()) + ".jpg");
    ui->image->setPixmap(pixmap.scaled(170, 200, Qt::KeepAspectRatio));
}
