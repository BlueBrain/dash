
/* Copyright (c) 2011-2012, EFPL/Blue Brain Project
 *                     Daniel Nachbaur <daniel.nachbaur@epfl.ch>
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

#include "contextChange.h"

#include <dash/node.h>


namespace dash
{
namespace detail
{

ContextChange::ContextChange( const Type t, NodePtr n, dash::NodePtr c )
    : Change( t, n, c )
{
}

ContextChange::ContextChange( const Type t, NodePtr n, dash::AttributePtr a )
    : Change( t, n, a )
{
}

ContextChange::ContextChange( dash::AttributePtr a,
                              boost::weak_ptr< lunchbox::Any > v )
    : Change( a )
    , value( v )
{
}

bool ContextChange::operator == ( const ContextChange& rhs ) const
{
    if( this == &rhs || Change::operator ==( rhs ))
        return true;

    return value.expired() || rhs.value.expired() ||
           *value.lock() == *rhs.value.lock();
}

}
}
