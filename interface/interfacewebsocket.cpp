#include "interfacewebsocket.h"

InterfaceWebSocket::InterfaceWebSocket(const QUrl &url , QObject *parent) : QObject(parent),
    monURL(url)
{
    //creation d'un client WebSocket
    myserver.open(QUrl(url)); //Connexion au serveur WebSocket
}

void InterfaceWebSocket::envoyerSignal(QByteArray message)
{
    //On envoie le trame d'alerte
    qDebug() << " message a l'envoie";
    myserver.sendBinaryMessage(message);
}

void InterfaceWebSocket::envoyerSignal()
{
    //on envoie le signal de data disponible
    qDebug() << " message a l'envoie";
    myserver.sendBinaryMessage(QByteArray(1,'A'));
}






