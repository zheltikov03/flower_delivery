#ifndef MAKINGORDER_H
#define MAKINGORDER_H

#include <QDialog>

#include "user.h"
#include "bouquet.h"

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
    QList<bouquet>* bouquets;
    static const QString imagesFile;
    int bouquetIndex;
private slots:
    void makeOrder();
    void selectBouquet(const QModelIndex &index);
};

#endif // MAKINGORDER_H
