#include "order.h"

int order::getId(){
    return id;
}

int order::getUserID(){
    return userID;
}

int order::getBouquetID(){
    return bouquetID;
}

int order::getFloristID(){
    return floristID;
}

int order::getCourierID(){
    return courierID;
}

int order::getStatus(){
    return status;
}

QString order::getAddress(){
    return address;
}

time_t order::getDateTime(){
    return dateTime;
}

QString order::getDopInfo(){
    return dopInfo;
}

void order::setId(int id){
    this->id = id;
}

void order::setUserID(int userID){
    this->userID = userID;
}

void order::setBouquetID(int bouquetID){
    this->bouquetID = bouquetID;
}

void order::setFloristID(int floristID){
    this->floristID = floristID;
}

void order::setCourierID(int courierID){
    this->courierID = courierID;
}

void order::setStatus(int status){
    this->status = status;
}

void order::setAddress(QString address){
    this->address = address;
}

void order::setDateTime(time_t dateTime){
    this->dateTime = dateTime;
}

void order::setDopInfo(QString dopInfo){
    this->dopInfo = dopInfo;
}
