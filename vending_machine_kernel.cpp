#include "vending_machine_kernel.h"

Vending_Machine_kernel::Vending_Machine_kernel()
{

}

double Vending_Machine_kernel::print_sum() const
{
    return base_info._sum;
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
    base_info._sum_in_dispay += sum;
}



