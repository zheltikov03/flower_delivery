#include "user.h"

int user::getId()
{
    return id;
}

QString user::getName()
{
    return name;
}

QString user::getPhone()
{
    return phone;
}

QString user::getPassword(){
    return password;
}

int user::getStatus()
{
    return status;
}

void user::setId(int id)
{
    this->id = id;
}

void user::setName(QString name)
{
    this->name = name;
}

void user::setPhone(QString phone)
{
    this->phone = phone;
}

void user::setPassword(QString password){
    this->password = password;
}

void user::setStatus(int status)
{
    this->status = status;
}
