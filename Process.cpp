#include "Process.h"

Process::Process(){
}

Process::~Process(){
}

void Process::launch(SpinalCore::Event event){
    if(event.event_num != 1){
        qDebug() << "test";
    }
}


