
/* Copyright (c) 2011-2012, EPFL/Blue Brain Project
 *                     Stefan Eilemann <stefan.eilemann@epfl.ch>
 *
 * This file is part of DASH <https://github.com/BlueBrain/dash>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef DASH_DETAIL_CHANGE_H
#define DASH_DETAIL_CHANGE_H

#include "node.h"
#include "types.h"

#include <dash/api.h>

#include <ostream>


namespace dash
{
namespace detail
{

/** A base class for changes. */
class Change
{
public:
    enum Type
    {
        NONE,
        NODE_INSERT,
        NODE_ERASE,
        ATTRIBUTE_INSERT,
        ATTRIBUTE_ERASE,
        ATTRIBUTE_CHANGED
    };

    Change() : type( NONE ) {}
    Change( dash::AttributePtr a );
    Change( const Type t, NodePtr n, dash::NodePtr c );
    Change( const Type t, NodePtr n, dash::AttributePtr a );
    Change( const Change& rhs );

    bool operator == ( const Change& rhs ) const;
    bool operator != ( const Change& rhs ) const { return !(*this == rhs); }

    Type type;
    NodePtr node;
    dash::NodePtr child;
    dash::AttributePtr attribute;
};

DASH_API std::ostream& operator << ( std::ostream& os, const Change& change );
DASH_API std::ostream& operator << ( std::ostream& os,
                                     const Change::Type& type );



}
}

#endif // DASH_DETAIL_CHANGE_H
