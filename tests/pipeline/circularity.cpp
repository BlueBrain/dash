
/* Copyright (c) 2011-2012, EPFL/Blue Brain Project
 *                     Ahmet Bilgili
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

#include <dash/context.h>
#include <dash/attribute.h>
#include <dash/node.h>

#include <dash/detail/node.h>

#include <lunchbox/thread.h>
#include <lunchbox/mtQueue.h>

#define THREAD_COUNT    4
#define INCREMENT_CONST 11
#define ITERATION_COUNT 5000
#define ATTR_INIT_VALUE 0
#define ATTR_EXIT_VALUE -1


typedef lunchbox::MTQueue< dash::Commit, ITERATION_COUNT > CommitQueue;

bool modifyTree( dash::NodePtr nodePtr )
{
    for( dash::Node::AttributeIterator it = nodePtr->attributesBegin();
         it != nodePtr->attributesEnd(); ++it )
    {
        int val = (*it)->get< int >();

        if( val == ATTR_EXIT_VALUE )
        {
            *(*it) = ATTR_EXIT_VALUE;
            return false;
        }
        // Create multiple changes
        *(*it) = val + INCREMENT_CONST;
    }

    for( dash::Node::ChildIterator it = nodePtr->childrenBegin();
         it != nodePtr->childrenEnd();  ++it )
    {
        if( !modifyTree( *it ) )
            return false;
    }

    return true;
}

class TestThread: public lunchbox::Thread
{
public:
    TestThread()
        :inputQ_( 0 ), outputQ_( 0 )
    {
    }

    void setInputQueue(CommitQueue* input) { inputQ_ = input; }
    void setOutputQueue(CommitQueue* output) { outputQ_ = output; }

    virtual ~TestThread()
    {
        context_.setCurrent( );
        context_.commit( );  // consume remaining changes
    }

    virtual void run()
    {
        context_.setCurrent();
        while( true )
        {
            dash::Commit commit = inputQ_->pop();
            context_.apply( commit );
            const bool result = modifyTree( tree_ );
            commit = context_.commit();
            outputQ_->push( commit );
            if( !result )
                exit( );
        }
    }

    void setTree( const dash::NodePtr tree ) { tree_ = tree; }
    dash::Context& getContext() { return context_; }

private:

    dash::Context context_;
    CommitQueue* inputQ_;
    CommitQueue* outputQ_;
    dash::NodePtr tree_;
};


int dash::test::main( int argc, char **argv )
{
    dash::Context& mainCtx = dash::Context::getMain( argc, argv );
    {
        CommitQueue mainCtxOutputQueue;
        CommitQueue queues[ THREAD_COUNT - 1 ];
        CommitQueue mainCtxInputQueue;

        TestThread threads[ THREAD_COUNT ];

        threads[ 0 ].setInputQueue( &mainCtxOutputQueue );
        for(int i = 1; i < THREAD_COUNT - 1; ++i)
        {
            threads[ i - 1 ].setOutputQueue( &queues[ i ] );
            threads[ i ].setInputQueue( &queues[ i ] );
        }
        threads[ THREAD_COUNT - 1 ].setOutputQueue( &mainCtxInputQueue );

        // Create a simple tree
        dash::NodePtr rootNodePtr = new dash::Node( );
        dash::NodePtr child0NodePtr = new dash::Node( );
        dash::NodePtr child1NodePtr = new dash::Node( );
        dash::NodePtr child00NodePtr = new dash::Node( );
        dash::NodePtr child01NodePtr = new dash::Node( );
        dash::NodePtr child10NodePtr = new dash::Node( );
        dash::NodePtr child11NodePtr = new dash::Node( );

        rootNodePtr->insert( child0NodePtr );
        mainCtx.commit( );
        rootNodePtr->insert( child1NodePtr );
        mainCtx.commit( );
        child0NodePtr->insert( child00NodePtr );
        mainCtx.commit( );
        child0NodePtr->insert( child01NodePtr );
        mainCtx.commit( );
        child1NodePtr->insert( child10NodePtr );
        mainCtx.commit( );
        child1NodePtr->insert( child11NodePtr );
        mainCtx.commit( );

        // child0NodePtr
        dash::AttributePtr attrib00 = new dash::Attribute( ATTR_INIT_VALUE+0 );
        child0NodePtr->insert( attrib00 );
        mainCtx.commit( );

        // child1NodePtr
        dash::AttributePtr attrib10 = new dash::Attribute( ATTR_INIT_VALUE+1 );
        dash::AttributePtr attrib11 = new dash::Attribute( ATTR_INIT_VALUE+2 );
        child1NodePtr->insert( attrib10 );
        mainCtx.commit( );
        child1NodePtr->insert( attrib11 );
        mainCtx.commit( );

        // For the child00NodePtr
        dash::AttributePtr attrib000 = new dash::Attribute( ATTR_INIT_VALUE+3 );
        dash::AttributePtr attrib001 = new dash::Attribute( ATTR_INIT_VALUE+4 );
        child00NodePtr->insert( attrib000 );
        mainCtx.commit( );
        child00NodePtr->insert( attrib001 );
        mainCtx.commit( );

        // For the child01NodePtr
        dash::AttributePtr attrib010 = new dash::Attribute( ATTR_INIT_VALUE+5 );
        child01NodePtr->insert( attrib010 );
        mainCtx.commit( );

        // For the child10NodePtr
        dash::AttributePtr attrib100 = new dash::Attribute( ATTR_INIT_VALUE+6 );
        dash::AttributePtr attrib101 = new dash::Attribute( ATTR_INIT_VALUE+7 );
        child10NodePtr->insert( attrib100 );
        mainCtx.commit( );
        child10NodePtr->insert( attrib101 );
        mainCtx.commit( );

        // For the child11NodePtr
        dash::AttributePtr attrib110 = new dash::Attribute( ATTR_INIT_VALUE+8 );
        child11NodePtr->insert( attrib110 );
        mainCtx.commit( );

        threads[ 0 ].setInputQueue( &mainCtxOutputQueue );
        for(int i = 0; i < THREAD_COUNT -1; ++i)
        {
            threads[ i ].setOutputQueue( &queues[ i ] );
            threads[ i + 1 ].setInputQueue( &queues[ i ] );
        }
        threads[ THREAD_COUNT -1 ].setOutputQueue( &mainCtxInputQueue );

        for(int i = 0; i < THREAD_COUNT; ++i)
        {
            threads[ i ].setTree( rootNodePtr );
            mainCtx.map( rootNodePtr, threads[ i ].getContext( ) );
        }

        for(int i = 0; i < THREAD_COUNT; ++i)
            threads[ i ].start();

        for(int i = 0; i < ITERATION_COUNT; i++ )
        {
            modifyTree( rootNodePtr );

            // Trigger exit on the threads
            if( i == ( ITERATION_COUNT - 1 ) ) { *attrib00 = ATTR_EXIT_VALUE; }

            mainCtxOutputQueue.push( mainCtx.commit( ) );

            mainCtx.apply( mainCtxInputQueue.pop( ) );
        }

        for(int i = 0; i < THREAD_COUNT; ++i)
            threads[ i ].join();

        const int totalIncrement = INCREMENT_CONST * ( ITERATION_COUNT - 1 ) *
                                   ( THREAD_COUNT + 1 ) + INCREMENT_CONST;

        int receivedValue = attrib00->get< int >( );
        int expectedValue = ATTR_EXIT_VALUE;
        TESTINFO( receivedValue == expectedValue,
                  receivedValue << "!=" << expectedValue);

        receivedValue = attrib10->get< int >( );
        expectedValue = ATTR_INIT_VALUE + 1 + totalIncrement;
        TESTINFO( receivedValue == expectedValue,
                  receivedValue << "!=" << expectedValue);

        receivedValue = attrib11->get< int >( );
        expectedValue = ATTR_INIT_VALUE + 2 + totalIncrement;
        TESTINFO( receivedValue == expectedValue,
                  receivedValue << "!=" << expectedValue);

        receivedValue = attrib000->get< int >( );
        expectedValue = ATTR_INIT_VALUE + 3 + totalIncrement;
        TESTINFO( receivedValue == expectedValue,
                  receivedValue << "!=" << expectedValue);

        receivedValue = attrib001->get< int >( );
        expectedValue = ATTR_INIT_VALUE + 4 + totalIncrement;
        TESTINFO( receivedValue == expectedValue,
                  receivedValue << "!=" << expectedValue);

        receivedValue = attrib010->get< int >( );
        expectedValue = ATTR_INIT_VALUE + 5 + totalIncrement;
        TESTINFO( receivedValue == expectedValue,
                  receivedValue << "!=" << expectedValue);

        receivedValue = attrib100->get< int >( );
        expectedValue = ATTR_INIT_VALUE + 6 + totalIncrement;
        TESTINFO( receivedValue == expectedValue,
                  receivedValue << "!=" << expectedValue);

        receivedValue = attrib101->get< int >( );
        expectedValue = ATTR_INIT_VALUE + 7 + totalIncrement;
        TESTINFO( receivedValue == expectedValue,
                  receivedValue << "!=" << expectedValue);

        receivedValue = attrib110->get< int >( );
        expectedValue = ATTR_INIT_VALUE + 8 + totalIncrement;
        TESTINFO( receivedValue == expectedValue
                  , receivedValue << "!=" << expectedValue);
    }

    mainCtx.commit();
    delete &mainCtx;

    return EXIT_SUCCESS;
}
