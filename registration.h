#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QMainWindow>

namespace Ui {
class registration;
}

class registration : public QMainWindow
{
    Q_OBJECT

public:
    explicit registration(QWidget *parent = nullptr);
    ~registration();

private slots:
    void reg();
    void loginWindow();

private:
    Ui::registration *ui;
    bool checkData();
};

#endif // REGISTRATION_H
