#include "bouquetsedit.h"
#include "ui_bouquetsedit.h"

bouquetsEdit::bouquetsEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bouquetsEdit)
{
    ui->setupUi(this);
}

bouquetsEdit::~bouquetsEdit()
{
    delete ui;
}
