#ifndef VENDING_MACHINE_KERNEL_H
#define VENDING_MACHINE_KERNEL_H

#include <QThread>
#include <QStack>
#include <QString>
#include <map>
#include <QMetaType>

#include "station.h"

struct base_information {
    double _sum_in_dispay = 0;

    double _sum = 0;

    QStack<QPair<QString,unsigned int>> vector_products[5];
};

class Vending_Machine_kernel : public QThread
{
    Q_OBJECT

public:
    Vending_Machine_kernel();

    double print_sum();

    void run();

public slots:
    //Учёт суммы в автоматe
    void get_sum (double sum);
    //Загрузка товара
    void get_product(QString& str,Station* station);
    //Выдать продукт
    void give_one_product(int num_lot);

signals:
    void product_to_box(QPair<QString,unsigned int>,int,double,int);
    //включить выдачу
    void _take(int);
    //включить сигнал пустаты лотка
    void _signal(int,bool);

private:
    const unsigned int max_size = 20;
    base_information base_info;
    char selector = -1;

    QString _str;
    Station* _station;
    int _num_lot = -1;
};

#endif // VENDING_MACHINE_KERNEL_H
