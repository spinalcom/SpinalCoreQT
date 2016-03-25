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

#include "SpinalCore.h"
#include "Com/ClientLoop.h"

int SpinalCore::_nb_inst = 0;
static QCoreApplication *qcore_application = 0;

SpinalCore::SpinalCore( const QHostAddress &address, quint16 port ) {
    if ( not _nb_inst++ ) {
        int argc = 0;
        char *argv[] = {};
        qcore_application = new QCoreApplication( argc, argv );
    }

    qevent_loop = 0;
    database = new Database;
    client_loop = new ClientLoop( database, address, port );

    connect( client_loop, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::QueuedConnection );
}

SpinalCore::~SpinalCore() {
    database->flush();
    delete client_loop;
    delete database;
    if ( --_nb_inst == 0 ) {
        delete qcore_application;
        qcore_application = 0;
    }
}

void SpinalCore::reg_type( QString type, bool auto_reg_model ) {
    if ( auto_reg_model )
        client_loop->reg_type_for_callback( type, this, SLOT(reg_type_callback_auto_reg(quint64)) );
    else
        client_loop->reg_type_for_callback( type, this, SLOT(reg_type_callback(quint64)) );
}

void SpinalCore::reg_model( const ModelPointer &mp ) {
    if ( Model *m = mp.model() )
        client_loop->reg_model( m, this, SLOT(change_callback(Model*)) );
}

ModelPointer SpinalCore::simple_load_ptr( quint64 ptr ) {
    return _wait_load( client_loop->load_ptr( ptr, this, SLOT(load_callback(Model*,int)) ) );
}

ModelPointer SpinalCore::simple_load( QString path ) {
    return _wait_load( client_loop->load( path, this, SLOT(load_callback(Model*,int)) ) );
}

bool SpinalCore::has_something_to_send() const {
    return client_loop->has_something_to_send();
}

int SpinalCore::pending_events_size() const{
    return pending_events.size();
}

SpinalCore::Event SpinalCore::event() {
    while ( true ) {
        if ( pending_events.size() ) {
            Event res = pending_events.front();
            pending_events.pop_front();
            return res;
        }
        _wait();
    }
}

bool SpinalCore::connected() const {
    return client_loop->connected();
}

void SpinalCore::_wait() {
    QEventLoop qe;
    qevent_loop = &qe;
    qevent_loop->exec();
}

void SpinalCore::_exit() {
    if ( qevent_loop ) {
        qevent_loop->exit();
        qevent_loop = 0;
    }
}


ModelPointer SpinalCore::_wait_load( int n ) {
    while ( true ) {
        _wait();
        for( int i = pending_events.size() - 1; i >= 0; --i ) {
            if ( pending_events[ i ].event_type == Event::Load and pending_events[ i ].n_callback == n ) {
                Model *res = pending_events[ i ].model;
                pending_events.remove( i );
                return ModelPointer( client_loop, res );
            }
        }
    }
}

void SpinalCore::reg_type_callback_auto_reg( quint64 ptr ) {
    client_loop->load_ptr( ptr, this, SLOT(load_for_reg_callback(Model*,int)) );
}

void SpinalCore::reg_type_callback( quint64 ptr ) {
    Event event;
    event.client_loop = client_loop;
    event.event_type = Event::RegType;
    event.event_num = 0;
    event.n_callback = 0;
    event.ptr = ptr;
    pending_events << event;

    emit new_event(event);
    _exit();
}

void SpinalCore::change_callback( Model *m ) {
    Event event;
    event.client_loop = client_loop;
    event.event_type = Event::Change;
    event.event_num = 0;
    event.model = m;
    pending_events << event;

    emit new_event(event);
    _exit();
}

void SpinalCore::force_callback( ) {
    Event event;
    event.client_loop = client_loop;
    event.event_type = Event::Change;
    event.event_num = 1;
    pending_events << event;

    emit new_event(event);
    _exit();
}

void SpinalCore::load_callback( Model *m, int n ) {
    Event event;
    event.client_loop = client_loop;
    event.event_type = Event::Load;
    event.event_num = 0;
    event.n_callback = n;
    event.model = m;
    pending_events << event;

    emit new_event(event);
    _exit();
}

void SpinalCore::load_for_reg_callback( Model *m, int n ) {
    if ( m )
        client_loop->reg_model( m, this, SLOT(change_callback(Model*)) );
}

void SpinalCore::disconnected() {
    Event event;
    event.client_loop = client_loop;
    event.event_type = Event::Disconnection;
    event.event_num = 0;
    pending_events << event;

    emit quit();
    _exit();
}

// API functions ==================================================

ModelPointer SpinalCore::load( QString path )
{
    ModelPointer loaded_model = SpinalCore::simple_load( path );
    SpinalCore::reg_model( loaded_model );
    return loaded_model;
}

ModelPointer SpinalCore::load_ptr( quint64 ptr )
{
    ModelPointer loaded_model = SpinalCore::simple_load_ptr( ptr );
    SpinalCore::reg_model( loaded_model );
    return loaded_model;
}

void SpinalCore::load_type( QString type )
{
    SpinalCore::reg_type( type );
}

// =================================================================



