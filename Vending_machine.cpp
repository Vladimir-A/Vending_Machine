#include "Vending_machine.h"
#include "ui_mainwindow.h"

Vending_machine::Vending_machine(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->refund->setReadOnly(true);

    _kernel  = new Vending_Machine_kernel;
    _stuff   = new Stuff;

    connect(this,SIGNAL(sent_summ_to_kernel(double)),_kernel,SLOT(get_sum(double)));
}

Vending_machine::~Vending_machine()
{
    delete ui;
}

void Vending_machine::on_Button1_clicked()
{
    //ui->LED1->toggle();
    ui->Btray1->setEnabled(true);

}

void Vending_machine::on_sum50_clicked()
{
    ui->sum_total->display(ui->sum_total->value()+50);
    emit sent_summ_to_kernel(50);
}

void Vending_machine::on_sum100_clicked()
{
    ui->sum_total->display(ui->sum_total->value()+100);
    emit sent_summ_to_kernel(100);
}

void Vending_machine::on_sum500_clicked()
{
    ui->sum_total->display(ui->sum_total->value()+500);
    emit sent_summ_to_kernel(500);
}

void Vending_machine::on_Button_refund_clicked()
{
    emit sent_summ_to_kernel(-1*(ui->sum_total->value()));
    ui->refund->setText(QString("%1").arg(ui->sum_total->value()));
    ui->sum_total->display(0);
}
