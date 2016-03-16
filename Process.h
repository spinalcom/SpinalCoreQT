#ifndef LAUNCHER_H
#define LAUNCHER_H
#include <src/Com/SpinalCore.h>
#include <QtCore/QProcess>
#include <QtCore/QList>


class Process : public QObject {
  Q_OBJECT
 public:
    Process();
    
    ~Process();
    
 public slots:
      void launch(SpinalCore::Event event);
      
 public: 
      SpinalCore* sc;                           //référence au SodaClient
      QList<MP> mp_list;                        //liste des container de données suivit
      int increment;                            //increment util dans la fonction launch
};


#endif // LAUNCHER_H
