#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "vending_machine_kernel.h"
#include "stuff.h"

namespace Ui {
class MainWindow;
}

class Vending_machine : public QMainWindow
{
    Q_OBJECT

public:
    explicit Vending_machine(QWidget *parent = 0);
    ~Vending_machine();

private slots:
    void on_Button1_clicked();

    void on_sum50_clicked();

    void on_sum100_clicked();

    void on_sum500_clicked();

    void on_Button_refund_clicked();

signals:
    void sent_summ_to_kernel(double sum);

private:
    Ui::MainWindow *ui;

    //Динамические объекты
    Vending_Machine_kernel *_kernel;
    Stuff *_stuff;
};

#endif // MAINWINDOW_H
