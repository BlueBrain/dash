
/* Copyright (c) 2012, EFPL/Blue Brain Project
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

#include "contextCommit.h"
#include "context.h"
#include "contextChange.h"

#include <dash/context.h>
#include <dash/node.h>


namespace dash
{
namespace detail
{

ContextCommit::ContextCommit()
     : contextChanges_()
     , context_()
{
}

ContextCommit::~ContextCommit()
{
}

ContextCommit& ContextCommit::operator = ( const ContextCommit& from )
{
    contextChanges_ = ContextChanges();
    context_.reset();
    return *this;
}

void ContextCommit::add( const ContextChange& change )
{
    LBASSERT( Context::getNumSlots() > 1 );

    if( !context_ )
        context_.reset( new dash::Context );

    if( change.type == Change::NODE_INSERT )
        dash::Context::getCurrent().map( change.child, *context_ );
    else if( change.type == Change::ATTRIBUTE_INSERT )
        dash::Context::getCurrent().map( change.attribute, *context_ );

    contextChanges_.push_back( change );
}

std::ostream& operator << ( std::ostream& os, const ContextCommit& commit )
{
    return os << commit.contextChanges_;
}

}
}
