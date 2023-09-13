#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QList>
#include <QJsonDocument>

#include "user.h"
#include "order.h"
#include "bouquet.h"

class database
{
private:
    static const QString usersFile;
    static const QString bouquetsFile;
    static const QString ordersFile;

    QJsonDocument* readJson(QString name);
    bool writeJson(QJsonDocument* doc, QString name);
public:
    user* authorization(QString phone, QString hash);
    user* getUser(int id);
    bool newUser(user* User);
    QList<order>* getOrders(user* User);
    QList<bouquet>* getBouquets();
    bool newOrder(order Order);
    bool changeOrderStatus(int id, int newStatus, int userId);
};

#endif // DATABASE_H
