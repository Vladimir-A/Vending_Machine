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
    int ptr_str = 0;
    for (int i = 0; i != 5; ++i){
        QString Name;
        while((_str[ptr_str] != '-') && (_str.size() != ptr_str)){
            Name.append(_str[ptr_str]);
            ptr_str++;
        }
        ptr_str++;
        if (Name == "nothing") continue;

        for (unsigned int j = base_info.vector_products[i].size(); j != max_size; j++){
            QPair<QString,unsigned int> pair(Name,_station->get_info(Name));
            base_info.vector_products[i].push_back(pair);
            emit product_to_box(pair,i);
        }
    }
}

void Vending_Machine_kernel::get_sum(double sum)
{
    base_info._sum_in_dispay += sum;
}

void Vending_Machine_kernel::get_product(QString &str, Station *station)
{
    _str = str;
    _station = station;
    this->start();
}



