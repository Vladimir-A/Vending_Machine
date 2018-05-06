#ifndef STATION_H
#define STATION_H

#include <QThread>

class Station : public QThread
{
    Q_OBJECT

public:
    Station(QObject *parent = nullptr);

    void run();
};

#endif // STATION_H
