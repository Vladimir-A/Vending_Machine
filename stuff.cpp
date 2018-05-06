#include "stuff.h"

Stuff::Stuff(QObject *parent) : QThread(parent)
{

}

double Stuff::print_cash() const
{
    return cash;
}

void Stuff::run()
{

}

void Stuff::get_income(double sum)
{
    cash += sum;
}
