#ifndef PRODUCT_H
#define PRODUCT_H

#include "QString"


class Product
{
public:
    Product();
    Product(const int p,const QString n);

private:
    unsigned int price = 0;
    QString name;
};

#endif // PRODUCT_H
