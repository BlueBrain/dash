
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

#ifndef DASH_DETAIL_COMMIT_H
#define DASH_DETAIL_COMMIT_H

#include "commitChange.h"

#include <dash/api.h>
#include <lunchbox/lfVector.h> // member
#include <lunchbox/serializable.h>
#include <lunchbox/types.h>


namespace dash
{
namespace detail
{

/** Internal implementation of the dash::Commit */
class Commit
{
public:
    DASH_API Commit();
    DASH_API ~Commit();

    Commit& operator = ( const ContextCommit& from );

    bool operator == ( const Commit& rhs ) const;
    bool operator != ( const Commit& rhs ) const { return !(*this == rhs); }

    bool empty() const { return changes_.empty(); }

    void apply() const;

private:
    LB_SERIALIZABLE

    friend int test::main( int argc, char **argv );
    friend std::ostream& operator << ( std::ostream& os, const Commit& commit );

    mutable CommitChanges changes_;

    boost::shared_ptr< dash::Context > context_;

    Commit( const Commit& from ); // disable copy
    Commit& operator = ( const Commit& from ); // disable assignment
};

inline std::ostream& operator << ( std::ostream& os, const Commit& commit )
{
    return os << commit.changes_;
}

template< class Archive >
inline void Commit::save( Archive& ar, const unsigned int ) const
{
    ar << changes_;
}

template< class Archive >
inline void Commit::load( Archive& ar, const unsigned int )
{
    ar >> changes_;
}

}
}

#endif // DASH_DETAIL_COMMIT_H
