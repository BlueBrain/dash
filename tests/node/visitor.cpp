
// Copyright (c) 2011 EPFL/BBP. All rights reserved.
// Author: Stefan Eilemann

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
    //co::base::sleep( 5000 );
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
