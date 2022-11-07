#ifndef INTERFACERUCHE_H
#define INTERFACERUCHE_H

#include <QObject>
#include <QSerialPort>
#include <QDebug>
#include <QString>
#include <QByteArray>
#include <entity/dataruche.h>
#include <chrono>
#include <ctime>
#include <fstream>

class InterfaceRuche : public QObject
{
    Q_OBJECT
public:
    explicit InterfaceRuche(QString port,QObject *parent = nullptr);
private:
    QString port;
    QSerialPort *comSerie;
    QByteArray trame;
    std::fstream fs;

    void configurationComSerie();

signals:
    void dataRucheDisponible(QString*);
    void erreur(QString*,int);
    void dataErreurDisponible(QByteArray);
public slots:
    void lireTrame();


};

#endif // INTERFACERUCHE_H
