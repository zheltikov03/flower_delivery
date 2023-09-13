#ifndef BOUQUET_H
#define BOUQUET_H

#include <QString>

class bouquet
{
private:
    int id;
    QString name;
    double price;
    int quantity;
public:
    int getId();
    QString getName();
    double getPrice();
    int getQuantity();

    void setId(int id);
    void setName(QString name);
    void setPrice(double price);
    void setQuantity(int quantity);
};

#endif // BOUQUET_H
