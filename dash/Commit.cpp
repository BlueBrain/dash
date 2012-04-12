
/* Copyright (c) 2011, EFPL/Blue Brain Project
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

#include "Commit.h"

#include <dash/Node.h>
#include "detail/Commit.h"
#include "detail/Change.h"
#include "detail/Serializable.h"

namespace dash
{

SERIALIZABLETEXTARCHIVE( Commit, SERIALIZABLEPLAIN )
SERIALIZABLEBINARYARCHIVE( Commit, SERIALIZABLEPLAIN )

Commit::Commit()
        : impl_( new detail::Commit )
{}

Commit::Commit( const Commit& from )
        : impl_( from.impl_ )
{}

Commit& Commit::operator = ( const Commit& from )
{
    impl_ = from.impl_;
    return *this;
}

bool Commit::operator == ( const Commit& rhs ) const
{
    if( this == &rhs )
        return true;
    return *impl_ == *rhs.impl_;
}

}
