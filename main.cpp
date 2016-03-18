#include "SpinalCoreQT/SpinalCore.h"

#include "Process.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QString IP = "127.0.0.1";
    QHostAddress adress( IP );
    QString port = "8890";
    SpinalCore* myConnector = new SpinalCore( adress, port.toInt() );
    
    ModelPointer myModel = myConnector->load( "__myApp__/myModel" );
    
    Process *myProcess = new Process();
    myProcess->connector = myConnector;
    myProcess->models << myModel;
    myConnector->reg_model( myModel );

    QObject::connect( myConnector, SIGNAL(new_event(SpinalCore::Event)), myProcess, SLOT(launch(SpinalCore::Event)) );
    QObject::connect( myConnector, SIGNAL(quit()), &app, SLOT(quit()) );

    return app.exec();

}
