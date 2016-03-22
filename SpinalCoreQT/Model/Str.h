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

#ifndef STR_H
#define STR_H

#include "Model.h"

/**
*/
class Str : public Model {
public:
    Str( QString _data );
    Str();

    virtual void     write_usr( BinOut &nut, BinOut &uut, Database *db );
    virtual void     write_str( QDebug dbg ) const;
    virtual operator QString  () const;
    virtual QString  type     () const;

    virtual bool    _set( const char *str, int len );

    QString _data;
};

#endif // STR_H
