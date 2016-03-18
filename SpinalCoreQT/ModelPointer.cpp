/*
 Copyright 2015 SpinalCom  www.spinalcom.com
  

 This file is part of SpinalCore.

 SpinalCore is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Soca is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the iModelPointerlied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
 You should have received a copy of the GNU General Public License
 along with Soca. If not, see <http://www.gnu.org/licenses/>.
*/


#include "Model/ModelWithAttrAndName.h"
#include "Model/LstWithType.h"
#include "Model/TypedArray.h"
#include "Model/Path.h"
#include "Model/Val.h"
#include "Model/Str.h"
#include "Model/Ptr.h"

#include <QtCore/QStringList>
#include "Com/ClientLoop.h"
#include "ModelPointer.h"


ModelPointer::ModelPointer( ClientLoop *c, Model *m, QString p ) : c( c ), m( m ), p( p ) {
}

ModelPointer::ModelPointer( ClientLoop *c, Model *m ) : c( c ), m( m ) {
}

ModelPointer::ModelPointer( Model *m ) : c( 0 ), m( m ) {
}

void ModelPointer::flush() {
    if ( c and c->db )
        c->db->flush();
}

ModelPointer::operator int() const {
    return m and not p.size() ? m->operator int() : 0;
}

ModelPointer::operator quint64() const {
    return m and not p.size() ? m->operator quint64() : 0;
}

ModelPointer::operator double() const {
    return m and not p.size() ? m->operator double() : 0;
}

ModelPointer::operator QString() const {
    return m and not p.size() ? m->operator QString() : 0;
}

ModelPointer ModelPointer::operator[]( QString path ) const {
    Model *res = m;
    QStringList l = path.split( '.' );
    for( int i = 0; res and i < l.size(); ++i ) {
        QStringList m = l[ i ].split( '[' );
        for( int j = 0; res and j < m.size(); ++j ) {
            QString n = m[ j ];
            if ( j ) {
                n.replace( ']', ' ' );
                n = n.trimmed();
            }
            Model *tModelPointer = res->attr( n );
            if ( tModelPointer == 0 and n.indexOf( '.' ) < 0 and n.indexOf( '/' ) < 0 )
                return ModelPointer( c, res, n );
            res = tModelPointer;
        }
    }
    return ModelPointer( c, res );
}

ModelPointer ModelPointer::operator[]( int index ) const {
    return ModelPointer( c, m and not p.size() ? m->attr( index ) : 0 );
}

quint64 ModelPointer::date_last_change() const {
    return m ? m->_date_last_change : 0;
}

bool ModelPointer::changed_from_ext() const {
    return m ? m->_changed_from_ext : false;
}

bool ModelPointer::has_been_modified() const {
    return m and not p.size() ? m->has_been_modified( c->db->cur_date ) : false;
}

bool ModelPointer::has_been_directly_modified() const {
    return m and not p.size() ? m->has_been_directly_modified( c->db->cur_date ) : false;
}

void ModelPointer::signal_change() {
    if ( c and m )
        c->signal_change( m );
}

ModelPointer ModelPointer::new_obj( QString type ) {
    return ModelPointer( 0, new ModelWithAttrAndName( type ) );
}

ModelPointer ModelPointer::new_lst( QString type ) {
    return ModelPointer( 0, new LstWithType( type ) );
}

ModelPointer ModelPointer::new_lst() {
    return ModelPointer( 0, new Lst );
}

ModelPointer ModelPointer::new_path( QString filename ) {
    return ModelPointer( 0, new Path( filename ) );
}

ModelPointer ModelPointer::new_file( QString name, ModelPointer model ) {
    ModelPointer res = new_obj( "File" );
    res[ "name" ] = name;
    res[ "_ptr" ] = new_ptr( model );
    res[ "_info" ] = new_obj();
    return res;
}

ModelPointer ModelPointer::new_ptr( ModelPointer model ) {
    return ModelPointer( 0, new Ptr( (qint64)model.m ) );
}

ModelPointer ModelPointer::new_typed_array_qint32() {
    return ModelPointer( 0, new TypedArray<qint32> );
}

QDebug operator<<( QDebug dbg, const ModelPointer &c ) {
    return dbg << c.m;
}

quint64 ModelPointer::get_server_id(){
    return model()->get_server_id(c->db);
}

Model *ModelPointer::conv( const ModelPointer &ModelPointer ) {
    return ModelPointer.p.size() ? 0 : ModelPointer.m;
}

Model *ModelPointer::conv( quint64 val ) {
    return new Val( val, 0 );
}

Model *ModelPointer::conv( quint32 val ) {
    return new Val( val, 0 );
}

Model *ModelPointer::conv( qint64 val ) {
    return new Val( val, 0 );
}

Model *ModelPointer::conv( qint32 val ) {
    return new Val( val, 0 );
}

Model *ModelPointer::conv( double val ) {
    return new Val( val );
}

Model *ModelPointer::conv( QString st ) {
    return new Str( st );
}


