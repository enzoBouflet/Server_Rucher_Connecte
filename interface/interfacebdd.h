#ifndef INTERFACEBDD_H
#define INTERFACEBDD_H

#include <QObject>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlResult>
#include <QDebug>
#include <QSqlError>
#include <entity/datastation.h>
#include <controller.h>
#include <chrono>
#include <ctime>
#include <fstream>
#include <QSettings>
#include "interfacewebsocket.h"

#define CONNEXION_BDD_NAME "rucher"

class InterfaceBDD : public QObject
{
    Q_OBJECT
public:
    explicit InterfaceBDD(Controller *controller, QSettings *conf,QObject *parent = nullptr);

    void connecter();
protected:
    QSqlDatabase db;
    QSqlQuery requete;
    bool etat;
    Controller * controleur;
    std::fstream fs;
    QSettings *conf;
    InterfaceWebSocket serveur;

signals:
    void transmissionReussie();
    void erreur(int);
public slots:
    void sauvegarderDonneMeteo(DataStation*);
    void sauvegarderDonneRuche(DataRuche*);
    void transmettreDataErreur(QByteArray);
};

#endif // INTERFACEBDD_H
