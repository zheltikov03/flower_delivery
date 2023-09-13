#include "authorization.h"
#include "ui_authorization.h"

#include <QCryptographicHash>
#include <QMessageBox>

#include "registration.h"
#include "user.h"
#include "database.h"
#include "orderlist.h"

authorization::authorization(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::authorization)
{
    ui->setupUi(this);
}

authorization::~authorization()
{
    delete ui;
}

void authorization::regWindow(){
    registration* reg = new registration;
    reg ->show();
    this->close();
}

void authorization::logIn(){
    database base;
    user* User = base.authorization(ui->phoneLine->text(), QString(QCryptographicHash::hash(ui->passLine->text().toUtf8(),QCryptographicHash::Md5).toHex()));
    if(User != NULL){
        QMessageBox::information(this, "Вход успешен", "Вы успешно вошли.");
        orderList* OrderList = new orderList(User);
        OrderList ->show();
        this->close();
    } else
        QMessageBox::critical(this, "Ошибка входа", "Проверьте правильность введённых логина и пароля.");
}
