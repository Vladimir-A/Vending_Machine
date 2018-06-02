#include "station.h"

Station::Station(QObject *parent) : QThread(parent)
{

}

void Station::run()
{

}

unsigned int Station::get_info(QString &str)
{
    try{
        return types.at(str);
    } catch(std::exception &ex) {
        return 0;
    }
}

void Station::new_type(QString &str)
{
    //получение имени
    QString sbuf;
    for (auto ch : str){
        if (ch == '-') break;
        sbuf.push_back(ch);
    }
    sbuf.resize(sbuf.size()-1);

    //получение размера
    QString value;
    int ptr = str.indexOf('-')+1;
    for (;ptr != (str.size());ptr++){
        value.push_back(str[ptr]);
    }

    types[sbuf] = value.toUInt();
}
