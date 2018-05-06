#ifndef VENDING_MACHINE_KERNEL_H
#define VENDING_MACHINE_KERNEL_H

#include <QThread>
#include <QVector>

//class Vending_machine;
struct base_information {
    double _sum_in_dispay = 0;

    double _sum = 0;

    QVector<Product> vector_products[5];
};

class Vending_Machine_kernel : public QThread
{
    Q_OBJECT

public:
    Vending_Machine_kernel();

    double print_sum() const;

    void run();

public slots:
    //Учёт суммы в автоматe
    void get_sum (double sum);


private:
    const unsigned int max_size = 20;
    base_information base_info;



};

#endif // VENDING_MACHINE_KERNEL_H
