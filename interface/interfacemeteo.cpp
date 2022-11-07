#include "interfacemeteo.h"

InterfaceMeteo::InterfaceMeteo(QString port, QObject *) :
    comSerie(new QSerialPort(this))
{
    // on ouvre le port Série et on viens le configurer juste après
    this->port = port;
    configurationComSerie();
}

void InterfaceMeteo::configurationComSerie()
{
    //configuration de la communication série  on sélectionne le port et on le configure
    comSerie->setPortName(port);
    comSerie->setBaudRate(QSerialPort::Baud9600);
    comSerie->setDataBits(QSerialPort::Data8);
    comSerie->setParity(QSerialPort::NoParity);
    comSerie->setStopBits(QSerialPort::OneStop);
    comSerie->setFlowControl(QSerialPort::NoFlowControl);
    if (comSerie->open(QIODevice::ReadWrite)) { // si on peut lire et ecrire sur le port
            qDebug()<< "Port Com Connection OK";
            connect(comSerie, &QSerialPort::readyRead, this, &InterfaceMeteo::lireTrame);
        } else {// sinon on affiche ecrit l'erreur dans le fichier log

        std::time_t t = std::time(nullptr);
        char mbstr[100];
        if (std::strftime(mbstr, sizeof(mbstr), "%A %c", std::localtime(&t)))
        fs.open("/home/pi/Documents/projet/0.9/applicationRaspberry/log.txt",std::fstream::app);
        fs << mbstr <<" :Erreur survenue lors de l'ouverture du port série : " << port.toStdString()<<std::endl;
        fs.close();

        }

}

void InterfaceMeteo::lireTrame()
{
    QByteArray lecture = comSerie->readLine();     // fonction pour lire la trame et la recevoir  ensuite on test quelle type de trame est-ce

    if(lecture.contains("$")){
        //effacer l'ancien contenu de la trame
        trame.clear();
        //ajouter $ dans la trame
        trame.append("$");
        //conserver ce qu'il y a après le dolar
        trame += lecture.split('$')[1];
    } else if (lecture.contains("\r")){
        //si \r\n
        //afficher la trame
        trame += lecture.split('\r')[0];

        qDebug()<<trame;


        //on recoit la trame et on la divise en plusieurs données dans un tableau de string
        QString Liste = QString(trame); // on convertie la liste en String
        QStringList liste = Liste.split(";");// on divise la liste entre chaque ";"

        unsigned char checksum = trame[0]; // on commence le calcul du checksum
                                           //calcul du checksum XOR Bit a Bit
        for(int i = 1; i < trame.count()-2; i++)
        {
            checksum ^= trame[i];
        }

        unsigned char crcRecu =  liste[liste.count()-1].toInt(nullptr,16); // on recupere le CRC de la trame recu

        if( checksum == crcRecu ){ // on compare le CRC calculé et celui reçu

            emit dataStationDisponible(&Liste); // si le checksum est bon on le transmet au controlleur
        }
        else
            emit erreur(&Liste,1); // sinon on transmet l'erreur





    } else{
        //dans tous les cas autre que $ ou \r\n
        trame+=lecture;
    }
}
