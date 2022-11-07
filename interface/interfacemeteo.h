#ifndef INTERFACEMETEO_H
#define INTERFACEMETEO_H

#include <QObject>
#include <QSerialPort>
#include <QDebug>
#include <QString>
#include <QByteArray>
#include <entity/datastation.h>
#include <chrono>
#include <ctime>
#include <fstream>

class InterfaceMeteo : public QObject
{
    Q_OBJECT
public:
    explicit InterfaceMeteo(QString port,QObject *parent = nullptr);

private:
    QString port;
    QSerialPort *comSerie;
    QByteArray trame;
    std::fstream fs;


    void configurationComSerie();

signals:
    void dataStationDisponible(QString*);
    void erreur(QString*,int);
public slots:
    void lireTrame();
};

#endif // INTERFACEMETEO_H
