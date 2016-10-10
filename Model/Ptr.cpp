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

#include "../Sys/BinOut.h"
#include "Ptr.h"

Ptr::Ptr( qint64 _data ) : _data( 0 ) {
}

void Ptr::write_usr( BinOut &nut, BinOut &uut, Database *db ) {
    uut << 'V' << get_server_id( db ) << quint64( _data );
}

void Ptr::write_str( QDebug dbg ) const {
    dbg.nospace() << _data;
}

Ptr::operator quint64() const {
    return _data;
}

QString Ptr::type() const {
    return "Ptr";
}

bool Ptr::_set( qint64 a ) {
    bool res = _data != a;
    _data = a;
    return res;
}
