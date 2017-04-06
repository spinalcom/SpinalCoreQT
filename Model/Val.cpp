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
#include "Val.h"

#include <limits>
#include <cmath>

Val::Val( qint64 man, qint32 exp ) : man( man ), exp( exp ) {
}

Val::Val( double val ) {
    //double frexp( val, exp2 );
    if ( isnan( val ) ) {
        man = 0;
        exp = std::numeric_limits<qint32>::max();
    } else if ( val ) {
        exp = qint32( log10( fabs( val ) ) - 17 );
        man = round( val / pow( 10.0, exp ) );

        if ( abs( man * pow( 10.0, exp ) - val ) > 1e-6 ) {
            // qDebug() << man << exp << "should give" << val;
            exp = 0;
            man = 0;
        }
    } else {
        exp = 0;
        man = 0;
    }
}


void Val::write_str( QDebug dbg ) const {
    if ( exp )
        dbg.nospace() << man << "e" << exp;
    else
        dbg.nospace() << man;
}

QString Val::type() const {
    return "Val";
}

bool Val::_set( qint64 a, qint32 b ) {
    if ( a != man or b != exp ) {
        man = a;
        exp = b;
        return true;
    }
    return false;
}

bool Val::_set( qint64 a ) {
    if ( a != man or exp ) {
        man = a;
        exp = 0;
        return true;
    }
    return false;
}

void Val::write_usr( BinOut &nut, BinOut &uut, Database *db ) {
    uut << 'X' << get_server_id( db ) << man << exp;
}

Val::operator int() const {
    return exp ? int( operator double() ) : man;
}

Val::operator quint64() const {
    return exp ? int( operator double() ) : man;
}

Val::operator double() const {
    if ( exp == std::numeric_limits<qint32>::max() )
        return NAN;
    return man * std::pow( 10.0, exp );
}
