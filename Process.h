#ifndef PROCESS_H
#define PROCESS_H
#include <SpinalCoreQT/SpinalCore.h>
#include <QtCore/QList>

class Process : public QObject {
    public:
        Process();
        ~Process();
        void onchange(SpinalCore::Event event);
        SpinalCore* connector;
        QList<ModelPointer> models;
};

#endif // PROCESS_H
