#include "Vending_machine.h"
#include "ui_mainwindow.h"

Vending_machine::Vending_machine(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ui->LED1->setTristate();
    ui->refund->setReadOnly(true);
    ui->line_income->setReadOnly(true);

    filling_comboBoxes("nothing");

    _kernel  = new Vending_Machine_kernel;
    _station = new Station;
    _stuff   = new Stuff;

    //Танец с бубном, для системы метакомпиляции Qt
    qRegisterMetaType< QPair<QString,uint>  >("Pair");

    //Связь автомата и ядра, записывает в ядро сумму которая введена и считает общую
    connect(this,SIGNAL(sent_summ_to_kernel(double)),_kernel,SLOT(get_sum(double)));

    //Нажате на кнопики выручки сотрудниками
    connect(this,SIGNAL(get_income_box(double)),_stuff,SLOT(get_income(double)));

    //
    connect(this,SIGNAL(sent_new_type_to_station(QString&)),_station,SLOT(new_type(QString&)));

    //Связь ядра и коробки по добавлению нового продукта
    connect(this,SIGNAL(sent_message_to_kernel_download_new_product(QString&,Station*)),_kernel,SLOT(get_product(QString&,Station*)));

    //
    connect(_kernel,SIGNAL(product_to_box(QPair<QString,uint>,int)),this,SLOT(filling_boxmachine(QPair<QString,uint>,int)));
}

Vending_machine::~Vending_machine()
{
    delete ui;
}

void Vending_machine::filling_comboBoxes(const QString &str)
{
    ui->comboBox1->addItem(str);
    ui->comboBox2->addItem(str);
    ui->comboBox3->addItem(str);
    ui->comboBox4->addItem(str);
    ui->comboBox5->addItem(str);
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

void Vending_machine::on_Button_income_clicked()
{
    emit get_income_box(_kernel->print_sum());
    ui->line_income->setText(QString("%1").arg(_stuff->print_cash()));
}

void Vending_machine::on_Button_insert_new_product_clicked()
{
    QString str;
    str.push_back(ui->Name_product->displayText());
    if (str.size() == 0) {
        ui->Name_product->clear();
        ui->Prise_product->clear();
        return;
    }

    filling_comboBoxes(str);

    str.push_back(" - ");
    str.push_back(ui->Prise_product->displayText());
    ui->list_product->addItem(str);

    emit sent_new_type_to_station(str);

    ui->Name_product->clear();
    ui->Prise_product->clear();
}

void Vending_machine::on_Binsert_product_clicked()
{
    QString  str;
    str.push_back(ui->comboBox1->currentText());    str.push_back('-');
    str.push_back(ui->comboBox2->currentText());    str.push_back('-');
    str.push_back(ui->comboBox3->currentText());    str.push_back('-');
    str.push_back(ui->comboBox4->currentText());    str.push_back('-');
    str.push_back(ui->comboBox5->currentText());

    emit sent_message_to_kernel_download_new_product(str,_station);
}

void Vending_machine::filling_boxmachine(QPair<QString, unsigned int> pairs, int ch)
{
    switch (ch) {
    case 0:
        ui->product_status1->setValue(20);
        ui->price1->display(static_cast<int>(pairs.second));
        ui->Button1->setText(pairs.first);
        break;
    case 1:
        ui->product_status2->setValue(20);
        ui->price2->display(static_cast<int>(pairs.second));
        ui->Button2->setText(pairs.first);
        break;
    case 2:
        ui->product_status3->setValue(20);
        ui->price3->display(static_cast<int>(pairs.second));
        ui->Button3->setText(pairs.first);
        break;
    case 3:
        ui->product_status4->setValue(20);
        ui->price4->display(static_cast<int>(pairs.second));
        ui->Button4->setText(pairs.first);
        break;
    case 4:
        ui->product_status5->setValue(20);
        ui->price5->display(static_cast<int>(pairs.second));
        ui->Button5->setText(pairs.first);
        break;
    default:
        break;
    }
}








