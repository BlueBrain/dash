
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

#include "test.h"

#include <dash/Attribute.h>
#include <dash/Context.h>
#include <dash/Node.h>

class Counter : public dash::Node::ConstVisitor
{
public:
    Counter() : down( 0 ), leaf( 0 ), up( 0 ) {}
    virtual ~Counter(){}
    virtual dash::VisitorResult visitDown( dash::NodeConstPtr node )
        {
            ++down;
            return dash::ACCEPT_CONTINUE;
        }
    virtual dash::VisitorResult visit( dash::AttributeConstPtr attribute )
        {
            ++leaf;
            return dash::ACCEPT_CONTINUE;
        }
    virtual dash::VisitorResult visitUp( dash::NodeConstPtr node )
        {
            ++up;
            return dash::ACCEPT_CONTINUE;
        }

    size_t down;
    size_t leaf;
    size_t up;
};

int dash::test::main( int argc, char **argv )
{
    dash::Context::getMain( argc, argv );
    //lunchbox::sleep( 5000 );
    {
        dash::NodePtr root = new dash::Node;
        {
            root->insert( new dash::Node );
            root->insert( new dash::Attribute );

            dash::NodePtr child = new dash::Node;
            root->insert( child );
            {
                child->insert( new dash::Node );
                child->insert( new dash::Node );
                child->insert( new dash::Node );
                child->insert( new dash::Attribute );
                child->insert( new dash::Attribute );
            }
            root->insert( new dash::Node );
        }

        Counter counter;
        TEST( root->accept( counter ) == dash::ACCEPT_CONTINUE );
        TESTINFO( counter.down == 7, counter.down );
        TEST( counter.leaf == 3 );
        TEST( counter.down == counter.up );
    }
    return EXIT_SUCCESS;
}
