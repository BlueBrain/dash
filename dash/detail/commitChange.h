
/* Copyright (c) 2011-2012, EPFL/Blue Brain Project
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

#ifndef DASH_DETAIL_COMMITCHANGE_H
#define DASH_DETAIL_COMMITCHANGE_H

#include "change.h"

#include <lunchbox/serializable.h>

#include <boost/serialization/shared_ptr.hpp>
#include <boost/shared_ptr.hpp>


namespace dash
{
namespace detail
{

/** A modification in a commit. */
class CommitChange : public Change
{
public:
    CommitChange() : Change() {}

    // cppcheck-suppress noExplicitConstructor
    CommitChange( const ContextChange& rhs );

    bool operator == ( const CommitChange& rhs ) const;
    bool operator != ( const CommitChange& rhs ) const
        { return !(*this == rhs); }

    boost::shared_ptr< lunchbox::Any > value;

private:
    LB_SERIALIZABLE
};

template< class Archive >
inline void CommitChange::save( Archive& ar, const unsigned int ) const
{
    ar << type;
    ar << node;
    ar << child;
    ar << attribute;
    ar << value;
}

template< class Archive >
inline void CommitChange::load( Archive& ar, const unsigned int )
{
    ar >> type;
    ar >> node;
    ar >> child;
    ar >> attribute;
    ar >> value;
}

}
}

#endif // DASH_DETAIL_COMMITCHANGE_H
