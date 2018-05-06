#ifndef STATION_H
#define STATION_H

#include <QThread>
#include <map>
#include <QString>

class Station : public QThread
{
    Q_OBJECT

public:
    Station(QObject *parent = nullptr);

    void run();

public slots:
    void new_type(QString &str);

private:
    std::map<QString,unsigned int> types;
};

#endif // STATION_H
