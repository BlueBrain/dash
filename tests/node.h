
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

#ifndef DASHTEST_NODE_H
#define DASHTEST_NODE_H

#include <dash/node.h>
#include <dash/attribute.h>


bool areEqual( dash::NodeConstPtr lhs, dash::NodeConstPtr rhs )
{
    if( *lhs != *rhs )
        return false;

    dash::Node::ConstChildIterator lhsIt = lhs->childrenBegin();
    dash::Node::ConstChildIterator rhsIt = rhs->childrenBegin();
    for( ; lhsIt != lhs->childrenEnd() && rhsIt != rhs->childrenEnd();
         ++lhsIt, ++rhsIt )
    {
        if( !areEqual( *lhsIt, *rhsIt ))
            return false;
    }

    return true;
}

dash::NodePtr createSampleNode()
{
    dash::NodePtr root = new dash::Node;
    {
        root->insert( new dash::Node );
        root->insert( new dash::Attribute( 5 ) );

        dash::NodePtr child = new dash::Node;
        root->insert( child );
        {
            child->insert( new dash::Node );
            child->insert( new dash::Node );
            child->insert( new dash::Node );
            child->insert( new dash::Attribute( std::string( "bla" )));
            child->insert( new dash::Attribute );
        }
        root->insert( new dash::Node );
    }
    return root;
}


#endif // DASHTEST_SERIALIZE_H
