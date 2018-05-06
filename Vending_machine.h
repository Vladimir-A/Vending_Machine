#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "vending_machine_kernel.h"
#include "station.h"
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

    void on_Button_income_clicked();

    void on_Button_insert_new_product_clicked();

signals:
    //Отправляет сумму в ядро автомата
    void sent_summ_to_kernel(double);
    //Нажате на секретную кнопку персоналом
    void get_income_box(double);
    //
    void sent_new_type_to_station(QString&);

private:
    Ui::MainWindow *ui;

    void filling_comboBoxes(const QString &str);

    //Динамические объекты
    Vending_Machine_kernel *_kernel;
    Station *_station;
    Stuff *_stuff;
};

#endif // MAINWINDOW_H
