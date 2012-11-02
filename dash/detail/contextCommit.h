
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

#ifndef DASH_DETAIL_CONTEXTCOMMIT_H
#define DASH_DETAIL_CONTEXTCOMMIT_H

#include "types.h"

namespace dash
{
namespace detail
{

/** A commit object holding pending changes for a context. */
class ContextCommit
{
public:
     ContextCommit();
     ~ContextCommit();

    ContextCommit& operator = ( const ContextCommit& from );

    void add( const ContextChange& change );

    bool empty() const { return contextChanges_.empty(); }

private:
    friend class Commit;
    friend int test::main( int argc, char **argv );
    friend std::ostream& operator << ( std::ostream& os,
                                       const ContextCommit& commit );

    ContextChanges contextChanges_;

    boost::shared_ptr< dash::Context > context_;

    ContextCommit( const ContextCommit& from ); // disable copy
};

std::ostream& operator << ( std::ostream& os, const ContextCommit& commit );



}
}

#endif // DASH_DETAIL_CONTEXTCOMMIT_H
