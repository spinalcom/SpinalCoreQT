/*
 Copyright 2015 SpinalCom - www.spinalcom.com
*
* This file is part of SpinalCore.
*
* Please read all of the following terms and conditions
* of the Free Software license Agreement ("Agreement")
* carefully.
*
* This Agreement is a legally binding contract between
* the Licensee (as defined below) and SpinalCom that
* sets forth the terms and conditions that govern your
* use of the Program. By installing and/or using the
* Program, you agree to abide by all the terms and
* conditions stated or referenced herein.
*
* If you do not agree to abide by these terms and
* conditions, do not demonstrate your acceptance and do
* not install or use the Program.
*
* You should have received a copy of the license along
* with this file. If not, see
* <http://resources.spinalcom.com/licenses.pdf>.
*/

#ifndef SpinalCore_H
#define SpinalCore_H

#ifdef METIL_COMP_DIRECTIVE
#pragma inc_path /usr/include/qt4
#endif // METIL_COMP_DIRECTIVE

#include <QtCore/QCoreApplication>
#include <QtNetwork/QHostAddress>
#include <QtCore/QVector>

#include "ModelPointer.h"


/**

*/
class SpinalCore : public QObject {
    Q_OBJECT
public:
    struct Event {
        enum { RegType, Load, Disconnection, Change };

        bool disconnection() const { return event_type == Disconnection; }
        bool reg_type() const { return event_type == RegType; }
        bool change() const { return event_type == Change; }
        bool load() const { return event_type == Load; }

        ModelPointer mp() { return ModelPointer( client_loop, model ); }
        operator bool() const { return event_type != Disconnection; }

        //
        class ClientLoop *client_loop;
        int event_type;
        int event_num;  /// sert à trier des evennements personalisés
        int n_callback;
        union {
            Model *model;
            quint64 ptr; ///< if RegType
        };
    };

    SpinalCore( const QHostAddress &address, quint16 port, qint32 userid, QString password );
    ~SpinalCore();

    void  reg_type( QString type, bool auto_reg_model = true ); ///< permit to get an event if an object of type $type is created on the server
    void  reg_model( const ModelPointer &mp ); ///< if changed, model will generate an Change event
    ModelPointer    simple_load_ptr( quint64 ptr ); ///< asynchronous load
    ModelPointer    simple_load( QString path ); ///< asynchronous load
    Event event(); ///< wait for an event

    bool   connected() const;
    bool   has_something_to_send() const;
    int    pending_events_size() const;

    void _wait();
    
signals:  
    void new_event(SpinalCore::Event);
    void quit();
   
private slots:
    void reg_type_callback_auto_reg( quint64 ptr ); ///< called if an object of a registered type is created on the server
    void reg_type_callback( quint64 ptr ); ///< called if an object of a registered type is created on the server
    void change_callback( Model *m ); ///<
    void force_callback( ); ///<
    void load_for_reg_callback( Model *m, int n ); ///<
    void load_callback( Model *m, int n ); ///<
    void disconnected(); ///<

private:
    void _exit(); ///< exit from qevent_loop
    ModelPointer   _wait_load( int n ); ///< asynchronous load

    class ClientLoop *client_loop;
    class QEventLoop *qevent_loop;
    class Database *database;

    QVector<Event> pending_events;

public:
    static int _nb_inst;
    
    // API functions ==============================================
    ModelPointer load( QString path ); // load and reg_model
    ModelPointer load_ptr( quint64 ptr ); // load_ptr and reg_model
    void load_type( QString type ); // reg_type
    // ============================================================

};

#endif // SpinalCore_H
