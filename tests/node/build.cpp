
/* Copyright (c) 2011-2012, EFPL/Blue Brain Project
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

#include <dash/Context.h>
#include <dash/Node.h>

#include <dash/detail/Attribute.h>
#include <dash/detail/Change.h>
#include <dash/detail/Commit.h>
#include <dash/detail/Context.h>
#include <dash/detail/Node.h>

#include <lunchbox/clock.h>
#include <lunchbox/init.h>
#include <lunchbox/thread.h>

#include <limits>

#define LEVELS 4
#define CHILDREN_PER_LEVEL 16

const size_t nThreads_ = 4; // per level!
co::base::a_ssize_t nOps_;

class Builder : public co::base::Thread
{
public:
    Builder() : level( LEVELS ) {}
    virtual ~Builder() {}

    virtual void run()
        {
            if( level == 1 )
            {
                for( size_t i = 0; i < CHILDREN_PER_LEVEL; ++i )
                {
                    dash::NodePtr child = new dash::Node;
                    node->insert( child );
                    ++nOps_;
                }
                return;
            }

            Builder threads[ nThreads_ ];
            for( size_t i = 0; i < CHILDREN_PER_LEVEL; i += nThreads_ )
            {
                for( size_t j = 0; j < nThreads_; ++j )
                {
                    threads[ j ].node = new dash::Node;
                    threads[ j ].level = level - 1;
                    node->insert( threads[ j ].node );
                    TEST( threads[ j ].start( ));
                    ++nOps_;
                }
                for( size_t j = 0; j < nThreads_; ++j )
                {
                    TEST( threads[ j ].join( ));
                }
            }
        }

    dash::NodePtr node;
    size_t level;
};

class Counter : public dash::Node::ConstVisitor
{
public:
    Counter() : nNodes( 0 ) {}
    virtual ~Counter() {}

    virtual dash::VisitorResult visitDown( dash::NodeConstPtr node )
        { ++nNodes; return dash::ACCEPT_CONTINUE; }
    size_t nNodes;
};

int dash::test::main( int argc, char **argv )
{
    dash::Context& context = dash::Context::getMain( argc, argv );
    //co::base::sleep( 5000 );

    Builder builder;
    builder.node = new dash::Node;
    nOps_ = 1;

    co::base::Clock clock;
    TEST( builder.start( ));
    TEST( builder.join( ));
    const float bTime = clock.getTimef();

    Counter counter;

    clock.reset();
    builder.node->accept( counter );
    const float cTime = clock.getTimef();

    TESTINFO( builder.node->getRefCount() == 1, builder.node->getRefCount( ));
    TESTINFO( size_t( nOps_ ) == counter.nNodes,
              nOps_ << " != " << counter.nNodes );

    std::cout << "        ops,    build/ms,     count/ms" << std::endl;
    std::cout << std::setw(11) << nOps_ << ", " << std::setw(11)
              << float(nOps_)/bTime << ", " << std::setw(11)
              << float(nOps_)/cTime << std::endl;

    builder.node = 0;
    {
        dash::Commit commit = context.commit();
        dash::detail::ChangesPtr changes = commit.getImpl()->changes_;
        TESTINFO( changes->empty(), *changes );
    }

    delete &context;
    return EXIT_SUCCESS;
}
