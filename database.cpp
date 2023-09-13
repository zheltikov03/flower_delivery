#include "database.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

const QString database::usersFile = "D:/университет/курсовой проекс/jsonExampleUsers.json";
const QString database::bouquetsFile = "D:/университет/курсовой проекс/jsonExampleBouquets.json";
const QString database::ordersFile = "D:/университет/курсовой проекс/jsonExampleOrders.json";

QJsonDocument* database::readJson(QString name){
    QString val;
    QFile file;
    file.setFileName(name);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!file.isOpen())
        return NULL;
    val = file.readAll();
    file.close();

    QJsonDocument* doc = new QJsonDocument(QJsonDocument::fromJson(val.toUtf8()));
    return doc;
}

bool database::writeJson(QJsonDocument* doc, QString name){
    QFile file;
    file.setFileName(name);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    if(!file.isOpen())
        return false;

    QString jsonString = doc->toJson(QJsonDocument::Indented);
    QTextStream stream( &file );
    stream << jsonString;
    file.close();
    return true;
}

user* database::authorization(QString phone, QString hash){
    QJsonDocument* doc = readJson(usersFile);
    if(doc == NULL)
        return NULL;
    QJsonArray users = doc->array();
    delete doc;
    QJsonObject json;
    user* User = new user;
    for(int i = 0; i < users.size(); i++){
        json = users.at(i).toObject();
        if(json["phone"].toString() == phone && json["password"].toString() == hash){
            User->setId(json["id"].toInt());
            User->setName(json["name"].toString());
            User->setPhone(json["phone"].toString());
            User->setStatus(json["status"].toInt());
            return User;
        }
    }
    delete User;
    return NULL;
}

user* database::getUser(int id){
    QJsonDocument* doc = readJson(usersFile);
    if(doc == NULL)
        return NULL;
    QJsonArray users = doc->array();
    delete doc;
    QJsonObject json;
    user* User = new user;
    for(int i = 0; i < users.size(); i++){
        json = users.at(i).toObject();
        if(json["id"].toInt() == id){
            User->setId(json["id"].toInt());
            User->setName(json["name"].toString());
            User->setPhone(json["phone"].toString());
            User->setStatus(json["status"].toInt());
            return User;
        }
    }
    delete User;
    return NULL;
}

bool database::newUser(user* User){
    QJsonDocument* doc = readJson(usersFile);
    if(doc == NULL)
        return false;
    QJsonArray users = doc->array();
    delete doc;

    QJsonObject userObject;
    userObject.insert("id", users.size());
    userObject.insert("name", User->getName());
    userObject.insert("phone", User->getPhone());
    userObject.insert("password", User->getPassword());
    userObject.insert("status", 0);

    users.insert(users.end(), userObject);
    QJsonDocument* docOut = new QJsonDocument(users);
    writeJson(docOut, usersFile);

    delete docOut;
    return true;
}

QList<order>* database::getOrders(user* User){
    QJsonDocument* doc = readJson(ordersFile);
    if(doc == NULL)
        return NULL;
    QJsonArray docArray = doc->array();

    QJsonObject json;
    QList<order>* orders = new QList<order>;
    order Order;
    for(int i = 0; i < docArray.size(); i++){
        json = docArray.at(i).toObject();
        if( (User->getStatus() == 0 && json["userID"].toInt() == User->getId())||
            (User->getStatus() == 1 && json["floristID"].toInt() == User->getId())||
            (User->getStatus() == 2 && json["courierID"].toInt() == User->getId())||
            (User->getStatus() == 1 && json["status"].toInt() == 0)||
            (User->getStatus() == 2 && json["status"].toInt() == 4) ){

            Order.setId(json["id"].toInt());
            Order.setUserID(json["userID"].toInt());
            Order.setBouquetID(json["bouquetID"].toInt());
            Order.setFloristID(json["floristID"].toInt());
            Order.setCourierID(json["courierID"].toInt());
            Order.setStatus(json["status"].toInt());
            Order.setAddress(json["address"].toString());
            Order.setDateTime(json["dateTime"].toString().toULongLong());
            Order.setDopInfo(json["dopInfo"].toString());

            orders->append(Order);
        }
    }
    return orders;
}

QList<bouquet>* database::getBouquets(){
    QJsonDocument* doc = readJson(bouquetsFile);
    if(doc == NULL)
        return NULL;
    QJsonArray docArray = doc->array();
    QJsonObject json;
    QList<bouquet>* bouquets = new QList<bouquet>;
    bouquet Bouquet;

    for(int i = 0; i < docArray.size(); i++){
        json = docArray.at(i).toObject();
        Bouquet.setId(json["id"].toInt());
        Bouquet.setName(json["name"].toString());
        Bouquet.setPrice(json["price"].toDouble());
        Bouquet.setQuantity(json["quantity"].toInt());

        bouquets->append(Bouquet);
    }
    return bouquets;
}

bool database::newOrder(order Order){
    QJsonDocument* doc = readJson(ordersFile);
    if(doc == NULL)
        return false;
    QJsonArray orders = doc->array();
    delete doc;

    QJsonObject orderObject;
    orderObject.insert("id", orders.size());
    orderObject.insert("userID", Order.getUserID());
    orderObject.insert("bouquetID", Order.getBouquetID());
    orderObject.insert("floristID", Order.getFloristID());
    orderObject.insert("courierID", Order.getCourierID());
    orderObject.insert("status", Order.getStatus());
    orderObject.insert("address", Order.getAddress());
    orderObject.insert("dateTime", QString::number(Order.getDateTime()));
    orderObject.insert("dopInfo", Order.getDopInfo());

    orders.insert(orders.end(), orderObject);
    QJsonDocument* docOut = new QJsonDocument(orders);
    writeJson(docOut, ordersFile);

    delete docOut;
    return true;
}

bool database::changeOrderStatus(int id, int newStatus, int userId){
    QJsonDocument* doc = readJson(ordersFile);
    if(doc == NULL)
        return false;
    QJsonArray orders = doc->array();
    delete doc;
    QJsonObject json;

    for(int i = 0; i < orders.size(); i++){
        json = orders.at(i).toObject();
        if(json["id"].toInt() == id){
            if( newStatus == 0 ||
                ((newStatus == 1 || newStatus == 2) && json["status"].toInt() != 0) ||
                (newStatus == 3 && json["status"].toInt() != 0) ||
                (newStatus == 4 && json["status"].toInt() != 3) ||
                (newStatus == 5 && json["status"].toInt() != 4) ||
                (newStatus == 6 && json["status"].toInt() != 5))
                return false;

            orders.removeAt(i);
            json["status"] = newStatus;
            if(newStatus == 3 || newStatus == 2)
                json["floristID"] = userId;
            else if(newStatus == 5)
                json["courierID"] = userId;

            orders.append(json);
            QJsonDocument* docOut = new QJsonDocument(orders);
            writeJson(docOut, ordersFile);

            delete docOut;
            return true;
        }
    }
    return false;
}

