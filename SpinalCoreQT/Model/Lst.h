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

#ifndef LST_H
#define LST_H

#include "Model.h"

/**

*/
class Lst : public Model {
public:
    Lst();

    virtual void    write_usr ( BinOut &nut, BinOut &uut, Database *db );
    virtual void    write_str ( QDebug  dbg ) const;
    virtual int     attr_index( QString key ) const;
    virtual Model  *attr      ( QString key ) const;
    virtual void    push      ( Model *m );
    virtual Model  *attr      ( int index   ) const;
    virtual int     size      () const;
    virtual QString type      () const;
    virtual bool    clear     ();

    virtual bool _set( int size, QVector<Model *> &model_stack, QVector<QString> &string_stack );

    QVector<Model *> _data;
};

#endif // LST_H
