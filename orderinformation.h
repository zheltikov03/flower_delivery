#ifndef ORDERINFORMATION_H
#define ORDERINFORMATION_H

#include <QDialog>

#include "user.h"
#include "order.h"

namespace Ui {
class orderinformation;
}

class orderinformation : public QDialog
{
    Q_OBJECT

public:
    explicit orderinformation(user* User, order Order, QWidget *parent = nullptr);
    ~orderinformation();

private:
    order Order;
    user* User;
    Ui::orderinformation *ui;
    void hideButtons();
    void activateButtons();
    void changeStatus(int newStatus, QString message);
private slots:
    void cancelOrder();
    void rejectOrder();
    void workFlorist();
    void completeFlorist();
    void workCourier();
    void completeCourier();
};

#endif // ORDERINFORMATION_H
