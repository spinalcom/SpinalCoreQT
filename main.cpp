#include <QtCore/QCoreApplication>
#include <QFont>
#include <QFile>

#include <QtCore/QProcess>
#include <QtCore/QList>
#include <QtCore/QTimer>

#include <src/Com/SpinalCore.h>
#include "config.h"
#include "Process.h"


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    SpinalCore::_nb_inst = 1;

// ouverture du fichier de configuration du plugin. ce fichier contient, l'IP serveur, le port, le conteneur de donnée auquel l'application doit s'inscrire
    config conf;
    conf.read_config();

// préparation de la connection au serveur et au container de données
    //instantiation du client Soda et du container de données
    QHostAddress adress1(conf.IP);                                  //adresse du serveur
    SpinalCore* sc = new SpinalCore( adress1, conf.port.toInt() );  //connection des client Soda avec le port
    MP object_id = sc->load(conf.data_container);                   //connection au container de données et référencement de son id temporaire

    //initialisation du laucher d'application a personnalisé
    Process *process = new Process();
    process->sc = sc;
    process->mp_list << object_id;                                  // ajout de l'id dans la liste des objets suivis
    sc->reg_model( object_id );                                      // inscription en tant qu'observateur de l'objet d'administration global


    QObject::connect(sc, SIGNAL(new_event(SpinalCore::Event)), process, SLOT(launch(SpinalCore::Event)));    //inscription d'un evennement launch lors d'un signal venant de l'objet
    QObject::connect(sc, SIGNAL(quit()), &app, SLOT(quit()));                                                 //fin du programme lorsqu'un serveur s'éteint


// codes de test
    //code de test avec un timer ok
    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), sc, SLOT(force_callback( )));
    timer->start(3000);


// lancement de la boucle d'evennement
    return app.exec();

};
