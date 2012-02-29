
// Copyright (c) 2011 EPFL/BBP. All rights reserved.
// Author: Stefan Eilemann

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
