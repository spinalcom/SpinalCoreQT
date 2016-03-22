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

#ifndef VAL_H
#define VAL_H

#include "Model.h"

/**
*/
class Val : public Model {
public:
    Val( qint64 man = 0, qint32 exp = 0 );
    Val( double val );

    virtual QString  type     () const;
    virtual bool     _set     ( qint64 a, qint32 b );
    virtual bool     _set     ( qint64 a );
    virtual void     write_str( QDebug dbg ) const;
    virtual void     write_usr( BinOut &nut, BinOut &uut, Database *db );
    virtual operator int      () const;
    virtual operator quint64  () const;
    virtual operator double   () const;

    qint64 man;
    qint32 exp;
};

#endif // VAL_H
