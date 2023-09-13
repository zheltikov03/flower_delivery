#include "bouquet.h"

int bouquet::getId(){
    return id;
}

QString bouquet::getName(){
    return name;
}

double bouquet::getPrice(){
    return price;
}

int bouquet::getQuantity(){
    return quantity;
}

void bouquet::setId(int id){
    this->id = id;
}

void bouquet::setName(QString name){
    this->name = name;
}

void bouquet::setPrice(double price){
    this->price = price;
}

void bouquet::setQuantity(int quantity){
    this->quantity = quantity;
}
