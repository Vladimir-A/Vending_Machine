#include "vending_machine_kernel.h"

Vending_Machine_kernel::Vending_Machine_kernel()
{

}

double Vending_Machine_kernel::print_sum()
{
    double buf = base_info._sum;
    base_info._sum = 0;
    return buf;
}

void Vending_Machine_kernel::run()
{
    switch (selector) {
    case 0:
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
            }
            emit product_to_box(base_info.vector_products[i][0],base_info.vector_products[i].size(),base_info._sum_in_dispay,i);
            emit _signal(i+1,true);
        }
        break;
    }
    case 1:
    {
        base_info._sum += base_info.vector_products[_num_lot][0].second;
        base_info._sum_in_dispay  -= base_info.vector_products[_num_lot][0].second;

        base_info.vector_products[_num_lot].pop_front();

        if (base_info.vector_products[_num_lot].size() != 0){
            emit product_to_box(base_info.vector_products[_num_lot][0],base_info.vector_products[_num_lot].size(),base_info._sum_in_dispay,_num_lot);
            emit _take(_num_lot+1);
        } else {
            emit product_to_box({"",0},0,0,_num_lot);
            emit _signal(_num_lot+1,false);
        }
        break;
    }
    default:
        break;
    }
    selector = -1;
}

void Vending_Machine_kernel::get_sum(double sum)
{
    base_info._sum_in_dispay += sum;
}

void Vending_Machine_kernel::get_product(QString &str, Station *station)
{
    _str = str;
    _station = station;
    selector = 0;
    this->start();
}

void Vending_Machine_kernel::give_one_product(int num_lot)
{
    _num_lot = num_lot - 1;
    //В 2 оператора if, так как в один работать будет некорректно
    if (base_info.vector_products[_num_lot].size() != 0) {
       if (base_info._sum_in_dispay >= base_info.vector_products[_num_lot][0].second){
           selector = 1;
           this->start();
       }
    } else {
        emit _signal(_num_lot+1,false);
    }
}



