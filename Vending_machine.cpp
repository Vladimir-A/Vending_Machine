#include "Vending_machine.h"
#include "ui_mainwindow.h"

Vending_machine::Vending_machine(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //начальная установка сигналов
    ui->LED1->click();
    ui->LED2->click();
    ui->LED3->click();
    ui->LED4->click();
    ui->LED5->click();

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
    connect(this,SIGNAL(sent_message_to_kernel_buy_product(int)),_kernel,SLOT(give_one_product(int)));

    //
    connect(_kernel,SIGNAL(product_to_box(QPair<QString,uint>,int,double,int)),this,SLOT(filling_boxmachine(QPair<QString,uint>,int,double,int)));

    //Cигнал для лотка(выдача)
    connect(_kernel,SIGNAL(_take(int)),this,SLOT(take(int)));
    connect(_kernel,SIGNAL(_signal(int,bool)),this,SLOT(signal_(int,bool)));
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
    emit sent_message_to_kernel_buy_product(1);
}


void Vending_machine::on_Btray1_clicked()
{
    ui->Btray1->setEnabled(false);
    ui->Btray1->setText("");
}

void Vending_machine::on_Button2_clicked()
{
    emit sent_message_to_kernel_buy_product(2);
}

void Vending_machine::on_Btray2_clicked()
{
    ui->Btray2->setEnabled(false);
    ui->Btray2->setText("");
}

void Vending_machine::on_Button3_clicked()
{
    emit sent_message_to_kernel_buy_product(3);
}

void Vending_machine::on_Btray3_clicked()
{
    ui->Btray3->setEnabled(false);
    ui->Btray3->setText("");
}

void Vending_machine::on_Button4_clicked()
{
    emit sent_message_to_kernel_buy_product(4);
}

void Vending_machine::on_Btray4_clicked()
{
    ui->Btray4->setEnabled(false);
    ui->Btray4->setText("");
}

void Vending_machine::on_Button5_clicked()
{
    emit sent_message_to_kernel_buy_product(5);
}

void Vending_machine::on_Btray5_clicked()
{
    ui->Btray5->setEnabled(false);
    ui->Btray5->setText("");
}

void Vending_machine::take(int ch)
{
    switch (ch) {
    case 1:
        ui->Btray1->setEnabled(true);
        ui->Btray1->setText("take");
        break;
    case 2:
        ui->Btray2->setEnabled(true);
        ui->Btray2->setText("take");
        break;
    case 3:
        ui->Btray3->setEnabled(true);
        ui->Btray3->setText("take");
        break;
    case 4:
        ui->Btray4->setEnabled(true);
        ui->Btray4->setText("take");
        break;
    case 5:
        ui->Btray5->setEnabled(true);
        ui->Btray5->setText("take");
        break;
    default:
        break;
    }
}

void Vending_machine::signal_(int ch, bool on_off)
{
    switch (ch) {
    case 1:{
        if (on_off){
            if (ui->LED1->isChecked())
                ui->LED1->click();
        } else {
            if (!ui->LED1->isChecked())
                ui->LED1->click();
        }
        break;
    }
    case 2:{
        if (on_off){
            if (ui->LED2->isChecked())
                ui->LED2->click();
        } else {
            if (!ui->LED2->isChecked())
                ui->LED2->click();
        }
        break;
    }
    case 3:{
        if (on_off){
            if (ui->LED3->isChecked())
                ui->LED3->click();
        } else {
            if (!ui->LED3->isChecked())
                ui->LED3->click();
        }
        break;
    }
    case 4:{
        if (on_off){
            if (ui->LED4->isChecked())
                ui->LED4->click();
        } else {
            if (!ui->LED4->isChecked())
                ui->LED4->click();
        }
        break;
    }
    case 5:{
        if (on_off){
            if (ui->LED5->isChecked())
                ui->LED5->click();
        } else {
            if (!ui->LED5->isChecked())
                ui->LED5->click();
        }
        break;
    }
    default:
        break;
    }
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
    bool test_uint;
    ui->Prise_product->displayText().toUInt(&test_uint);
    if ((ui->Prise_product->displayText() == "") || (!test_uint)) {
        ui->Name_product->clear();
        ui->Prise_product->clear();
        return;
    }
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

void Vending_machine::filling_boxmachine(QPair<QString, unsigned int> pairs, int _size, double _sum,int ch)
{
    switch (ch) {
    case 0:
        ui->product_status1->setValue(_size);
        ui->price1->display(static_cast<int>(pairs.second));
        ui->Button1->setText(pairs.first);
        ui->sum_total->display(_sum);
        break;
    case 1:
        ui->product_status2->setValue(_size);
        ui->price2->display(static_cast<int>(pairs.second));
        ui->Button2->setText(pairs.first);
        ui->sum_total->display(_sum);
        break;
    case 2:
        ui->product_status3->setValue(_size);
        ui->price3->display(static_cast<int>(pairs.second));
        ui->Button3->setText(pairs.first);
        ui->sum_total->display(_sum);
        break;
    case 3:
        ui->product_status4->setValue(_size);
        ui->price4->display(static_cast<int>(pairs.second));
        ui->Button4->setText(pairs.first);
        ui->sum_total->display(_sum);
        break;
    case 4:
        ui->product_status5->setValue(_size);
        ui->price5->display(static_cast<int>(pairs.second));
        ui->Button5->setText(pairs.first);
        ui->sum_total->display(_sum);
        break;
    default:
        break;
    }
}

