#include <QCoreApplication>
#include <interface/interfacemeteo.h>
#include <controller.h>
#include <QDebug>
#include <interface/interfacebdd.h>
#include <QSettings>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //création d'un fichier Settings permettant de changer des paramètres sans recompiler l'application
    QSettings conf("groupe1","beetoring");



    if(conf.value("entree/ruche").isNull()) {
       conf.setValue("entree/ruche","/dev/ttyACM1");
       conf.setValue("entree/meteo","/dev/ttyACM0");
       conf.setValue("BDD/ip","127.0.0.1");
       conf.setValue("BDD/port","3306");
       conf.setValue("BDD/nom","rucher");
       conf.setValue("BDD/password","1234");
       conf.setValue("BDD/username","root");
    }else qDebug() << "Fichier configuration trouvé Existe" << conf.fileName();

    InterfaceMeteo meteo(conf.value("entree/meteo").toString());
    InterfaceRuche ruche(conf.value("entree/ruche").toString());
    Controller controleur(&meteo,&ruche);
    InterfaceBDD interface(&controleur,&conf);
    return a.exec();
}
