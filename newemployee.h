#ifndef NEWEMPLOYEE_H
#define NEWEMPLOYEE_H

#include <QDialog>

namespace Ui {
class newEmployee;
}

class newEmployee : public QDialog
{
    Q_OBJECT

public:
    explicit newEmployee(QWidget *parent = nullptr);
    ~newEmployee();

private:
    Ui::newEmployee *ui;
};

#endif // NEWEMPLOYEE_H
