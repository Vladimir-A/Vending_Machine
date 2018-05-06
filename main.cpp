#include "Vending_machine.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Vending_machine w;
    w.show();

    return a.exec();
}
