#ifndef VENDING_MACHINE_KERNEL_H
#define VENDING_MACHINE_KERNEL_H

#include <QThread>

#include "station.h"

class Vending_machine;
class Vending_Machine_kernel : public QThread
{
    Q_OBJECT

public:
    Vending_Machine_kernel();

    void run();

public slots:
    void get_sum (double sum);

private:
    Station *_station;
    double _sum = 0;

};

#endif // VENDING_MACHINE_KERNEL_H
