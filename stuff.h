#ifndef STUFF_H
#define STUFF_H

#include <QThread>

class Stuff : public QThread
{
    Q_OBJECT

public:
    Stuff(QObject *parent = nullptr);

    void run();

private:
    unsigned long cash;
};

#endif // STUFF_H
