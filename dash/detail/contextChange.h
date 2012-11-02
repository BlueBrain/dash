
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

#ifndef DASH_DETAIL_CONTEXTCHANGE_H
#define DASH_DETAIL_CONTEXTCHANGE_H

#include "change.h"

#include <boost/weak_ptr.hpp>


namespace dash
{
namespace detail
{

/** A modification in a context. */
class ContextChange : public Change
{
public:
    ContextChange() : Change() {}
    ContextChange( const Type t, NodePtr n, dash::NodePtr c );
    ContextChange( const Type t, NodePtr n, dash::AttributePtr a );

    ContextChange( dash::AttributePtr a,
                   boost::weak_ptr< lunchbox::Any > value );

    bool operator == ( const ContextChange& rhs ) const;
    bool operator != ( const ContextChange& rhs ) const
        { return !(*this == rhs); }

    boost::weak_ptr< lunchbox::Any > value;
};

inline std::ostream& operator << ( std::ostream& os,
                                   const ContextChange& change )
{
    return os << static_cast< const Change& >( change );
}

}
}

#endif // DASH_DETAIL_CONTEXTCHANGE_H
