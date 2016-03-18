#ifndef LAUNCHER_H
#define LAUNCHER_H
#include <SpinalCoreQT/SpinalCore.h>
#include <QtCore/QList>

class Process : public QObject {
  Q_OBJECT
 public:
    Process();
    ~Process();
    
 public slots:
      void launch(SpinalCore::Event event);
      
 public: 
      SpinalCore* connector;
      QList<ModelPointer> models;
};

#endif // LAUNCHER_H
