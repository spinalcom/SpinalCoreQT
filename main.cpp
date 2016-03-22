#include "SpinalCoreQT/SpinalCore.h"

#include "process.h"

int main()
{
    // connect to the hub
    QString IP = "127.0.0.1";
    QHostAddress adress( IP );
    QString port = "8890";
    SpinalCore* myConnector = new SpinalCore( adress, port.toInt() );
    
    // synchronize models
    ModelPointer myModel = myConnector->sync_model( "__myApp__/Model" );
    myConnector->sync_type( "ModelType" );
    ModelPointer myPointedModel = myConnector->sync_ptr( Ptr );
    
    // use a process
    Process *myProcess = new Process();
    myProcess->connector = myConnector;
    myProcess->models << myModel;
    myProcess->models << myPointedModel;

    while ( SpinalCore::Event event = myConnector->event() ){
        myProcess->onchange( event );
    }
}

