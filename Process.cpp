#include <iostream>
#include <qglobal.h>
#include "Process.h"


Process::Process(){
    increment = 0;
};

Process::~Process(){
    qDebug() << "CLOSE LOOP";
};


void Process::launch(SpinalCore::Event event){
    if(event.event_num == 1){  // événement issu du timer

    qDebug() << "test launcher";
    }

    if(event.event_num != 1){  // événement issu d'une modification de l'objet sur le serveur

    }
};


