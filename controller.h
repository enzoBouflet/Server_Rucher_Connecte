#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <entity/dataruche.h>
#include <entity/datastation.h>
#include "interface/interfacemeteo.h"
#include "interface/interfaceruche.h"
#include <QDebug>
#include <chrono>
#include <ctime>
#include <fstream>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(InterfaceMeteo *meteo ,InterfaceRuche *ruche,QObject *parent = nullptr);
private:
    InterfaceMeteo *meteo;
    InterfaceRuche *ruche;
    DataStation *dataStation;
    DataRuche *dataRuche;
    std::fstream fs;

signals:
    void dataStationVersBDD(DataStation* data);
    void dataRucheVersBDD(DataRuche* data);
    void dataErreurVersInterfaceBDD(QByteArray);
public slots:
    void dataStationAEnvoyer(QString*);
    void dataRucheAEnvoyer(QString*);
    void dataErreurATraiter(QByteArray);
    void erreur(QString *);

};

#endif // CONTROLLER_H
