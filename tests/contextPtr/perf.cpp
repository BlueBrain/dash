
/* Copyright (c) 2011-2012, EPFL/Blue Brain Project
 *                          Stefan.Eilemann@epfl.ch
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

#define DASH_TEST_NO_WATCHDOG
#include "test.h"
#include "common.h"

#include <dash/context.h>
#include <dash/detail/contextPtr.h>

#include <lunchbox/clock.h>
#include <lunchbox/init.h>
#include <lunchbox/thread.h>

#include <boost/make_shared.hpp>

#include <limits>

#ifdef NDEBUG
#  ifdef __xlC__
const size_t nThreads_ = 8;
const size_t nLoops_ = 10000000;
#  else
const size_t nThreads_ = 4;
const size_t nLoops_ = 100000000;
#  endif
#else
const size_t nThreads_ = 4;
const size_t nLoops_ = 100000;
#endif

typedef dash::detail::ContextPtr< plain::Node > NodeCtxPtr;
NodeCtxPtr dashNode;
plain::NodePtr plainNode = boost::make_shared< plain::Node >();

class DashReader : public lunchbox::Thread
{
public:
    DashReader() {}
    virtual ~DashReader() {}

    virtual void run()
        {
            dash::Context context;
            dashNode.map( dash::Context::getCurrent().getImpl(),
                          context.getImpl( ));
            context.setCurrent();

            for( size_t i=0; i < nLoops_; ++i )
            {
                TEST( dashNode.get().get() == 42 );
            }
        }

};

class PlainReader : public lunchbox::Thread
{
public:
    PlainReader() {}
    virtual ~PlainReader() {}

    virtual void run()
        {
            for( size_t i=0; i < nLoops_; ++i )
            {
                TEST( plainNode->get() == 42 );
            }
        }

};

class DashWriter : public lunchbox::Thread
{
public:
    DashWriter() {}
    virtual ~DashWriter() {}

    virtual void run()
        {
            dash::Context context;
            dashNode.map( dash::Context::getCurrent().getImpl(),
                          context.getImpl( ));
            context.setCurrent();

            for( size_t i=0; i < nLoops_; ++i )
            {
                dashNode.getMutable().set( 17 );
            }
        }
};

class PlainWriter : public lunchbox::Thread
{
public:
    PlainWriter() {}
    virtual ~PlainWriter() {}

    virtual void run()
        {
            for( size_t i=0; i < nLoops_; ++i )
            {
                plainNode->set( 17 );
            }
        }
};

int dash::test::main( int , char ** )
{
    lunchbox::Clock clock;

    dashNode.setup();

    clock.reset();
#if 1
    DashReader dashReaders[ nThreads_ ];
    for( size_t i = 0; i < nThreads_; ++i )
    {
        TEST( dashReaders[i].start( ));
    }
    for( size_t i = 0; i < nThreads_; ++i )
    {
        TEST( dashReaders[i].join( ));
    }

    clock.reset();
    for( size_t i = 0; i < nThreads_; ++i )
    {
        TEST( dashReaders[i].start( ));
    }
    for( size_t i = 0; i < nThreads_; ++i )
    {
        TEST( dashReaders[i].join( ));
    }
#endif
    const float dashReadTime = clock.getTimef();


    clock.reset();
#if 1
    DashWriter dashWriters[ nThreads_ ];
    for( size_t i = 0; i < nThreads_; ++i )
    {
        TEST( dashWriters[i].start( ));
    }
    for( size_t i = 0; i < nThreads_; ++i )
    {
        TEST( dashWriters[i].join( ));
    }

    clock.reset();
    for( size_t i = 0; i < nThreads_; ++i )
    {
        TEST( dashWriters[i].start( ));
    }
    for( size_t i = 0; i < nThreads_; ++i )
    {
        TEST( dashWriters[i].join( ));
    }
#endif
    const float dashWriteTime = clock.getTimef();


    clock.reset();
#if 1
    PlainReader plainReaders[ nThreads_ ];
    for( size_t i = 0; i < nThreads_; ++i )
    {
        TEST( plainReaders[i].start( ));
    }
    for( size_t i = 0; i < nThreads_; ++i )
    {
        TEST( plainReaders[i].join( ));
    }

    clock.reset();
    for( size_t i = 0; i < nThreads_; ++i )
    {
        TEST( plainReaders[i].start( ));
    }
    for( size_t i = 0; i < nThreads_; ++i )
    {
        TEST( plainReaders[i].join( ));
    }
#endif
    const float plainReadTime = clock.getTimef();


    clock.reset();
#if 1
    PlainWriter plainWriters[ nThreads_ ];
    for( size_t i = 0; i < nThreads_; ++i )
    {
        TEST( plainWriters[i].start( ));
    }
    for( size_t i = 0; i < nThreads_; ++i )
    {
        TEST( plainWriters[i].join( ));
    }

    clock.reset();
    for( size_t i = 0; i < nThreads_; ++i )
    {
        TEST( plainWriters[i].start( ));
    }
    for( size_t i = 0; i < nThreads_; ++i )
    {
        TEST( plainWriters[i].join( ));
    }
#endif
    const float plainWriteTime = clock.getTimef();


    std::cout << "Type  dash time  plain time" << std::endl
              << "read  " << dashReadTime << "    " << plainReadTime << std::endl
              << "write " << dashWriteTime << "    " << plainWriteTime
              << std::endl;
    return EXIT_SUCCESS;
}
