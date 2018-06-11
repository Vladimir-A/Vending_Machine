#include "Vending_machine.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //qRegisterMetaType<QPair<QString,uint>>("Pair<QString,uint>");
    QApplication a(argc, argv);
    Vending_machine w;
    w.show();

    return a.exec();
}
