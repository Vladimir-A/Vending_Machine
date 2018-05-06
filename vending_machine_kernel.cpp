#include "vending_machine_kernel.h"

Vending_Machine_kernel::Vending_Machine_kernel()
{
    _station = new Station;

}

void Vending_Machine_kernel::run()
{
    for (;;){
        int t;
        t++;
        t--;
    }
}

void Vending_Machine_kernel::get_sum(double sum)
{
    _sum += sum;
}
