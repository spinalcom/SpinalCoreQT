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

#ifndef ModelPointer_H
#define ModelPointer_H

#include "Com/ClientLoop.h"
#include "Model/Lst.h"

/**
   Model Pointer. Permits operations on models
*/
class ModelPointer {
public:
    struct NewObj { QString type; };

    ModelPointer( ClientLoop *c, Model *m, QString p );
    ModelPointer( ClientLoop *c, Model *m );
    ModelPointer( Model *m = 0 );

    void flush(); ///< send modified data to ClientLoop

    void reassign( ModelPointer mp ) { if ( mp.c ) c = mp.c; m = mp.m; }

    ModelPointer operator[]( const char *path ) const { return operator[]( QString( path ) ); }
    ModelPointer operator[]( QString path ) const; ///< returns a sub-model
    ModelPointer operator[]( int index ) const; ///< returns a sub-model

    ModelPointer &operator=( const ModelPointer &val ) {
        if ( val.m ) {
            if ( p.size() and m ) {
                m->add_attr( p, val.m );
                if ( c )
                    c->signal_change( m );
                m = val.m;
                p.clear();
            } else if ( m and m->_set( val.m ) and c )
                c->signal_change( m );
        }
        return *this;
    }

    template<class T>
    ModelPointer &operator=( const T &val ) {
        if ( p.size() and m ) {
            Model *o = m;
            m = conv( val );
            o->add_attr( p, m );
            if ( c )
                c->signal_change( o );
            p.clear();
        } else if ( m and m->_set( val ) and c )
            c->signal_change( m );
        return *this;
    }

    template<class T>
    ModelPointer &operator<<( const T &val ) {
        if ( p.size() and m ) {
            Model *o = m;
            m = new Lst;
            o->add_attr( p, m );
            if ( c )
                c->signal_change( m );
            p.clear();
        }
        if ( m ) {
            m->push( conv( val ) );
            if ( c )
                c->signal_change( m );
        }
        return *this;
    }

    operator int    () const;
    operator quint64() const;
    operator double () const;
    operator QString() const;

    Model *model() const { return m; }
    QString type() const { return m ? m->type() : QString(); }
    int size() const { return m ? m->size() : 0; }
    void clear() { if ( m ) { if ( m->clear() and c ) c->signal_change( m ); } }
    bool ok() const { return m and not p.size(); }

    quint64 date_last_change() const;
    bool changed_from_ext() const;

    bool has_been_modified() const;
    bool has_been_directly_modified() const;

    void signal_change();

    static ModelPointer new_obj( QString type = "Model" );

    static ModelPointer new_lst();
    static ModelPointer new_lst( QString type ); ///< Lst with alternate type
    static ModelPointer new_path( QString filename );
    static ModelPointer new_file( QString name, ModelPointer model ); ///<
    static ModelPointer new_ptr( ModelPointer model );

    static ModelPointer new_typed_array_qint32();
    quint64 get_server_id(); ///<

private:
    friend QDebug operator<<( QDebug dbg, const ModelPointer &c );
    static Model *conv( const ModelPointer &mp );
    static Model *conv( quint64 val );
    static Model *conv( quint32 val );
    static Model *conv( qint64 val );
    static Model *conv( qint32 val );
    static Model *conv( double val );
    static Model *conv( QString st );

    ClientLoop *c;
    QString p;
    Model *m;
};


#endif // ModelPointer_H
