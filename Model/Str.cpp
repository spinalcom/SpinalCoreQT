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
#include "Str.h"

Str::Str( QString data ) : _data( data ) {
}

Str::Str() {
}

void Str::write_usr ( BinOut &nut, BinOut &uut, Database *db ) {
    uut << 'W' << get_server_id( db ) << _data;
}

void Str::write_str( QDebug dbg ) const {
    dbg.nospace() << _data;
}

Str::operator QString  () const {
    return _data;
}

QString Str::type() const {
    return "Str";
}

bool Str::_set( const char *str, int len ) {
    QString tmp = QString::fromUtf8( str, len );
    bool res = _data != tmp;
    _data = tmp;
    return res;
}
