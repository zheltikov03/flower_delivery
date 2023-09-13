#ifndef ORDERLIST_H
#define ORDERLIST_H

#include <QMainWindow>
#include <QList>
#include <QTimer>
#include <QListWidgetItem>

#include "user.h"
#include "order.h"

namespace Ui {
class orderList;
}

class orderList : public QMainWindow
{
    Q_OBJECT

public:
    explicit orderList(user* User, QWidget *parent = nullptr);
    ~orderList();

private:
    Ui::orderList *ui;
    user* User;
    QList<order>* orders = NULL;
    QTimer *timer;

private slots:
    void makingOrderWindow();
    void orderInformationWindow();
    void logOut();
    void reload();
};

#endif // ORDERLIST_H
