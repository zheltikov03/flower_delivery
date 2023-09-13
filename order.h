#ifndef ORDER_H
#define ORDER_H

#include <QString>

class order
{
private:
    int id;
    int userID;
    int bouquetID;
    int floristID;
    int courierID;
    int status;
    QString address;
    time_t dateTime;
    QString dopInfo;

public:
    int getId();
    int getUserID();
    int getBouquetID();
    int getFloristID();
    int getCourierID();
    int getStatus();
    QString getAddress();
    time_t getDateTime();
    QString getDopInfo();

    void setId(int id);
    void setUserID(int userID);
    void setBouquetID(int bouquetID);
    void setFloristID(int floristID);
    void setCourierID(int courierID);
    void setStatus(int status);
    void setAddress(QString address);
    void setDateTime(time_t dateTime);
    void setDopInfo(QString dopInfo);
};

#endif // ORDER_H
