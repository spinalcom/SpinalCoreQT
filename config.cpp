#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "config.h"

config::config()
{
    fileName = "organ.conf";
}


void config::read_config(){

    QFile fichier(fileName);
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&fichier);
    // traitement des ligne du fichier
    QString ligne;
    int n_ligne = 0;
    while(! flux.atEnd())
    {
        ligne = flux.readLine();
        if (n_ligne == 1){ //IP du serveur
            IP = ligne;
            qDebug() << IP;
        }else if (n_ligne == 3){ //port du serveur
            port = ligne;
            qDebug() << port;
        }else if (n_ligne == 5){ //port du serveur
            data_container = ligne;
            qDebug() << data_container;
        }
        n_ligne += 1;
    }

}
