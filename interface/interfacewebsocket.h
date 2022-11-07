#ifndef INTERFACEWEBSOCKET_H
#define INTERFACEWEBSOCKET_H

#include <QObject>
#include <QWebSocket>
/* La classe ici sert a faire le lien entre l'application
 * qui permet d'envoyer les messages d'alertes et celle-ci
 * l'application ici ce connecte au serveur de l'application d'alerte
 * et lui transmet des datas lors de la receptions d'un trame */
class InterfaceWebSocket : public QObject
{
    Q_OBJECT
public:
    explicit InterfaceWebSocket(const QUrl &url , QObject *parent = nullptr);
    void envoyerSignal(QByteArray);
    void envoyerSignal();
private:
    QWebSocket myserver;
    QUrl monURL;

};

#endif // INTERFACEWEBSOCKET_H
