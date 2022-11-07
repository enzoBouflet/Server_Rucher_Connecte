#include "controller.h"

Controller::Controller(InterfaceMeteo *meteo,InterfaceRuche *ruche,QObject *parent) : QObject(parent),
    dataStation(new DataStation()),
    dataRuche(new DataRuche())
{
    this->meteo=meteo;
    this->ruche=ruche;
    // mise en place des signaux qui permettent de créer des interruptions
    connect(meteo, &InterfaceMeteo::dataStationDisponible, this, &Controller::dataStationAEnvoyer);
    connect(ruche, &InterfaceRuche::dataRucheDisponible, this, &Controller::dataRucheAEnvoyer);
    connect(meteo ,&InterfaceMeteo::erreur,this, &Controller::erreur);
    connect(ruche ,&InterfaceRuche::erreur,this, &Controller::erreur);
}

void Controller::dataStationAEnvoyer(QString *trame)
{


    //on recoit la trame et on la divise en plusieurs données dans un tableau de string
    // on convertie la liste en String
    QStringList liste = trame->split(";");// on divise la liste entre chaque ";"

   /*   Les trames recus sont rangées dans l'ordre établie selon
    * le protocole ce qui permet de les rangé
    * dans les variables sans les modifiées
    * car si la data arrive ici alors le CRC est valide.
    *   Les valeurs converties en Double puis divisé par 10
    * sont recu en entier mais en 1/10 ex pour 10° la data
    * recu est de 100
    */
    dataStation->setPression(liste[1].toInt()); // envoyer les datas de la trames dans l'entité dataStation
    dataStation->setTemperature(liste[2].toDouble()/10);
    dataStation->setHumidite(liste[3].toDouble()/10);
    dataStation->setVMax(liste[4].toInt());
    dataStation->setVMoy(liste[5].toInt());
    // si les données de direction de vents sont nul alors on rentre 999 dans la BDD pour signifier valeur NULL
    if(liste[6].toUtf8() == "NaN")dataStation->setAngleDirection(999);
    else dataStation->setAngleDirection(liste[6].toInt());


  emit dataStationVersBDD(dataStation);
}

void Controller::dataRucheAEnvoyer(QString *trame)
{


    //on recoit la trame et on la divise en plusieurs données dans un tableau de string
    // on convertie la liste en String
    QStringList liste = trame->split(";");// on divise la liste entre chaque ";"



    dataRuche->setId(liste[1].toInt());
    dataRuche->setTemperature(liste[2].toDouble()/10); // envoyer les datas de la trames dans l'entité dataStation
    dataRuche->setHumidite(liste[3].toDouble()/10);
    dataRuche->setPoid(liste[4].toDouble()/10);
    dataRuche->setBascule(liste[5].toInt());
    dataRuche->setBatterie(liste[6].toDouble()/10);
    dataRuche->setLatitude(liste[7].toDouble());
    dataRuche->setLongitude(liste[8].toDouble());

    emit dataRucheVersBDD(dataRuche);
}

void Controller::dataErreurATraiter(QByteArray trame)
{
    //on emmet un signal qui sera recu par l'interface BDD
    emit dataErreurVersInterfaceBDD(trame);
}

void Controller::erreur(QString *trame)
{
    // on écrit dans les logs une erreur de réception de trame avec l'heure a laquelle celle ci c'est produite
    std::time_t t = std::time(nullptr);
    char mbstr[100];
    if (std::strftime(mbstr, sizeof(mbstr), "%A %c", std::localtime(&t)))
    fs.open("/home/pi/log.txt",std::fstream::app);                                                                  // on ouvre un fichier texte
    fs << mbstr <<" : Erreur survenue lors de la reception de la trame voici la trame :"<< trame << std::endl;      // on écrit dans le fichier
    fs.close();                                                                                                     // on ferme le fichier

}
