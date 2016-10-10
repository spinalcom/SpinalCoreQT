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

#ifndef DATABASE_H
#define DATABASE_H

#include "../Model/Model.h"
#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QSet>
class ClientLoop;

/**
*/
class Database : public QObject {
    Q_OBJECT
public:
    Database();
    ~Database();
    Model  *model( qint64 m ) const; ///< server_id -> local Model *
    Model  *signal_change( Model *m, bool from_ext = false ); ///<
    void    tmp_id_to_real( qint64 old_ptr, qint64 new_ptr );
    quint64 new_tmp_server_id( Model *m );
    void    flush();

private slots:
    void    end_round(); ///<

signals:
    void    _model_sig( Model * );

public:
    QMap<qint64,Model *> model_map;      ///< server_id -> local Model *
    QSet<ClientLoop *>   clients;        ///<
    QSet<Model *>        changed_models; ///< not the most efficient containers...
    quint64              prev_tmp_server_id;
    quint64              cur_date;
    bool                 reg_changes;    ///<
    bool                 end_round_timer; ///<

private:
    void _call_onchange_rec( Model *m );
    void _call_onchange_loc( Model *m, int add );
};

#endif // DATABASE_H
