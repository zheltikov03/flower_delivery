#include "newemployee.h"
#include "ui_newemployee.h"

newEmployee::newEmployee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newEmployee)
{
    ui->setupUi(this);
}

newEmployee::~newEmployee()
{
    delete ui;
}
