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

#ifndef BINOUT_H
#define BINOUT_H

#ifdef METIL_COMP_DIRECTIVE
#pragma inc_path /usr/include/qt4
#endif // METIL_COMP_DIRECTIVE
#include <QtCore/QByteArray>
#include <QtCore/QString>

/**
*/
class BinOut {
public:
    BinOut &operator<<( const BinOut &out ) {
        _data.append( out._data );
        return *this;
    }

    BinOut &operator<<( const QString &str ) {
        QByteArray tmp = str.toLatin1();
        *this << int( tmp.size() );
        _data.append( tmp );
        return *this;
    }

    template<class T>
    BinOut &operator<<( const T &v ) {
        _data.append( reinterpret_cast<const char *>( &v ), sizeof( T ) );
        return *this;
    }

    BinOut &write( const char *ptr, int len ) {
        _data.append( ptr, len );
        return *this;
    }

    void clear() { _data.clear(); }
    int size() const { return _data.size(); }

    const QByteArray &data() const { return _data; }

private:
    QByteArray _data;
};

#endif // BINOUT_H
