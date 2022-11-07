#include "interfacebdd.h"


InterfaceBDD::InterfaceBDD(Controller *controller, QSettings *conf, QObject *parent) :
    QObject(parent),
    controleur(controller),
    conf(conf),
    serveur(QUrl(QStringLiteral("ws://localhost:1234"))) // création du clients websocket si l'adresse/port est changé dans l'application d'alerte il faut le changer ici aussi
{
    connect(controller,&Controller::dataStationVersBDD,this,&InterfaceBDD::sauvegarderDonneMeteo);    
    connect(controller,&Controller::dataRucheVersBDD,this,&InterfaceBDD::sauvegarderDonneRuche);
    connect(controller,&Controller::dataErreurVersInterfaceBDD,this,&InterfaceBDD::transmettreDataErreur);

    connecter();
}

void InterfaceBDD::connecter()
{
    //affichage des drivers SQL disponible (optionnel)
    //si QMYSQL n'apparaît pas
    //alors vérifiez l'installation

    //si la connexion existe
    if(QSqlDatabase::contains(CONNEXION_BDD_NAME))
    {
        //récupérer la base de données existantes
        db = QSqlDatabase::database(CONNEXION_BDD_NAME);
    }
    else
    {
        //sinon ajouter un nouvelle connexion à la base
        db = QSqlDatabase::addDatabase("QMYSQL",CONNEXION_BDD_NAME);

        //adresse serveur et port
        db.setHostName(conf->value("BDD/ip").toString());
        db.setPort(conf->value("BDD/port").toInt());

        //nom de la base de données
        db.setDatabaseName(conf->value("BDD/nom").toString());

        //login et mot de passe
        db.setUserName(conf->value("BDD/username").toString());
        db.setPassword(conf->value("BDD/password").toString());
    }

    //connexion à la base de données
    //teste si la connexion exixte
    if(db.isOpen())
    {
        qDebug() << "Connexion a la BDD est déjà etablie";
    }
    else
    {
        //connexion avec teste et affichage du résultat
        if(db.open())
        {
            qDebug() << "Connexion a la BDD etablie";
        }
        else
        {
            //si la connexion a la BDD ne peut se faire on viens le noter dans le fichier log avec l'heure
            std::time_t t = std::time(nullptr); // les 3 lignes ici permettent de récuperer l'heure local
            char mbstr[100];
            if (std::strftime(mbstr, sizeof(mbstr), "%A %c", std::localtime(&t)))
            fs.open("/home/pi/log.txt",std::fstream::app);
            fs << mbstr <<" : Erreur survenue lors de l'ouverture de la BDD"  <<std::endl;
            fs.close();
        }
    }
}

void InterfaceBDD::sauvegarderDonneMeteo(DataStation *data)
{
    QSqlQuery requete(db); // on créer une requete vers la BDD

    requete.prepare("INSERT INTO `mesurestation` (`idMesureStation`, `horodatage`, `maxVent`,"
    " `moyvent`, `direcVent`, `temperature`, `humidite`, `pression`, `integriteCapteurVent`)"
    "VALUES (NULL, CURRENT_TIME() , :vMax , :vMoy,:direction,:temp,:humidite,:pression,:integriteCapteur);");   // on viens ecrire la requete mais sans les valeurs on leurs donne juste un identifiant

    requete.bindValue(":vMax",data->getVMax()); // on viens remplacer les identifaitns par les valeurs qui sont contenue dans botre classe DataStation
    requete.bindValue(":vMoy",data->getVMoy());
    requete.bindValue(":direction",data->getAngleDirection());
    requete.bindValue(":temp",data->getTemperature());
    requete.bindValue(":humidite",data->getHumidite());
    requete.bindValue(":pression",data->getPression());
    requete.bindValue(":integriteCapteur",1);
    if(!requete.exec()){ // si la requete ne viens pas s'executer on viens le noter dans les logs
        std::time_t t = std::time(nullptr);
        char mbstr[100];
        if (std::strftime(mbstr, sizeof(mbstr), "%A %c", std::localtime(&t)))
        fs.open("/home/pi/log.txt",std::fstream::app);
        fs << mbstr <<" : Erreur survenue lors de l'insertion de données station dans la BDD"<< std::endl;
        fs.close();
    }
    serveur.envoyerSignal(); //on appelle la methode envoyer signal de la classe InterfaceWebSocket qui va envoyer un signal a l'application permettant de gérer les seuils et les alertes
}

void InterfaceBDD::sauvegarderDonneRuche(DataRuche *data)
{
    QSqlQuery requete(db); //meme execution que la méthode sauvegarderDonneMeteo qui permet ici de sauvegarder les données rpvenant des ruches

    requete.prepare("INSERT INTO `dataruche` (`idRuche`, `idDataRuche`, `temperature`, `humidite`, `poids`, `bascule`, `longitude`, `latitude`, `batterie`)"
                    "VALUES (:idRuche, NULL, :temperature, :humidite, :poid, :bascule, :latitude, :longitude, :batterie);)");

    requete.bindValue(":idRuche",data->getId());
    requete.bindValue(":temperature",data->getTemperature());
    requete.bindValue(":humidite",data->getHumidite());
    requete.bindValue(":poid",data->getPoid());
    requete.bindValue(":bascule",data->getBascule());
    requete.bindValue(":latitude",data->getLatitude());
    requete.bindValue(":longitude",data->getLongitude());
    requete.bindValue(":batterie",data->getBatterie());
    if(!requete.exec()){
        std::time_t t = std::time(nullptr);
        char mbstr[100];
        if (std::strftime(mbstr, sizeof(mbstr), "%A %c", std::localtime(&t)))
        fs.open("/home/pi/log.txt",std::fstream::app);
        fs << mbstr <<": Erreur survenue lors de l'insertion de données ruche dans la BDD"<< std::endl;
        fs.close();
    }
    serveur.envoyerSignal();
}

void InterfaceBDD::transmettreDataErreur(QByteArray message)
{
    //si on recoit un signal d'alerte provenant des ruches on va transmettre les datas a l'application de gestion d'alertes
    serveur.envoyerSignal(message);
}

