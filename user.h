#ifndef USER_H
#define USER_H

#include <QString>

class user
{
private:
    int id;
    QString name;
    QString phone;
    QString password;
    int status;
public:
    int getId();
    QString getName();
    QString getPhone();
    QString getPassword();
    int getStatus();

    void setId(int id);
    void setName(QString name);
    void setPhone(QString phone);
    void setPassword(QString password);
    void setStatus(int status);
};

#endif // USER_H
