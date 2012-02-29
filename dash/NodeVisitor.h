
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

#ifndef DASH_NODEVISITOR_H
#define DASH_NODEVISITOR_H

#include <dash/types.h>
#include <dash/VisitorResult.h> // return value

namespace dash
{

/** A visitor to traverse a Node graph. */
template< class N, class A > class NodeVisitor
{
public:
    /** Construct a new node visitor. @version 0.1 */
    NodeVisitor(){}
        
    /** Destruct the node visitor. @version 0.1 */
    virtual ~NodeVisitor(){}  

    /** Visit a node on a down traversal. @version 0.1 */
    virtual VisitorResult visitDown( N )
        { return ACCEPT_CONTINUE; }

    /** Visit an attribute on the down traversal. @version 0.1 */
    virtual VisitorResult visit( A )
        { return ACCEPT_CONTINUE; }

    /** Visit a node on a up traversal. @version 0.1 */
    virtual VisitorResult visitUp( N )
        { return ACCEPT_CONTINUE; }
};

}

#endif // DASH_NODEVISITOR_H
