#include "registration.h"
#include "ui_registration.h"

#include <QCryptographicHash>
#include <QMessageBox>

#include "authorization.h"
#include "user.h"
#include "database.h"

registration::registration(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::registration)
{
    ui->setupUi(this);
}

registration::~registration()
{
    delete ui;
}

bool registration::checkData(){
    QRegularExpression phoneRegex("^(8|\\+7)?\\d{10}$");
    if (!phoneRegex.match(ui->phoneLine->text()).hasMatch()) {
        QMessageBox::warning(this, "Ошибка в номере телефона", "Номер телефона начинается с +7 или с 8 и состоит из 11 цифр.");
        return false;
    }
    if (ui->passLine->text().length() < 6) {
        QMessageBox::warning(this, "Ошибка в пароле", "Пароль должен состоять из 7 и более символов.");
        return false;
    }
    if (ui->passLine->text() != ui->repassLine->text()) {
        QMessageBox::warning(this, "Ошибка в пароле", "Пароли не совпадают.");
        return false;
    }
    return true;
}


void registration::reg(){
    if(!checkData())
        return;
    user* User = new user;
    User->setName(ui->nameLine->text());
    User->setPhone(ui->phoneLine->text());
    User->setPassword(QString(QCryptographicHash::hash(ui->passLine->text().toUtf8(),QCryptographicHash::Md5).toHex()));
    User->setStatus(0);
    database base;
    if(!base.newUser(User))
        QMessageBox::critical(this, "Ошибка","Не удалось записать данные в файл!");
    else{
        QMessageBox::about(this, "Успешно","Регистрация прошла успешно!");
        loginWindow();
    }
}

void registration::loginWindow(){
    authorization* auth = new authorization;
    auth ->show();
    this->close();
    delete this;
}
