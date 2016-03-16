/*
 Copyright 2015 SpinalCom  www.spinalcom.com
  

 This file is part of SpinalCore.

 SpinalCore is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Soca is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
 You should have received a copy of the GNU General Public License
 along with Soca. If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef LSTWITHTYPE_H
#define LSTWITHTYPE_H

#include "Lst.h"

/**

*/
class LstWithType : public Lst {
public:
    LstWithType( QString type );
    virtual QString underlying_type() const;

    QString _type;
};

#endif // LSTWITHTYPE_H
