#ifndef STUFF_H
#define STUFF_H

#include <QThread>

class Stuff : public QThread
{
    Q_OBJECT

public:
    Stuff(QObject *parent = nullptr);

    double print_cash() const;

    void run();

public slots:
    //Взять выручку из автомата
    void get_income(double sum);

private:
    //Сумма на руках у сотрудников
    double cash = 0;
};

#endif // STUFF_H
