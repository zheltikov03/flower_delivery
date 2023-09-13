#ifndef MAKINGORDER_H
#define MAKINGORDER_H

#include <QDialog>

#include "user.h"
#include "bouquet.h"
#include "order.h"

namespace Ui {
class makingorder;
}

class makingorder : public QDialog
{
    Q_OBJECT

public:
    explicit makingorder(user* User, QWidget *parent = nullptr);
    ~makingorder();

private:
    Ui::makingorder *ui;
    user* User;
    order newOrder;
    QList<bouquet>* bouquets;
    static const QString imagesFile;
    int bouquetIndex;
private slots:
    void nextBouquet();
    void previousBouquet();
    void makeOrder();
};

#endif // MAKINGORDER_H
