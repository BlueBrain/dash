
/* Copyright (c) 2005-2012, Stefan Eilemann <eile@equalizergraphics.com> 
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 2.1 as published
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

#ifndef DASHTEST_TEST_H
#define DASHTEST_TEST_H

#include <dash/detail/types.h>
#include <lunchbox/log.h>
#include <lunchbox/sleep.h>
#include <lunchbox/thread.h>
#include <fstream>

#define OUTPUT lunchbox::Log::instance( __FILE__, __LINE__ )

#define TEST( x )                                                       \
    {                                                                   \
        LBVERB << "Test " << #x << std::endl;                           \
        if( !(x) )                                                      \
        {                                                               \
            OUTPUT << #x << " failed" << std::endl;                     \
            ::exit( EXIT_FAILURE );                                     \
        }                                                               \
    }

#define TESTINFO( x, info )                                             \
    {                                                                   \
        LBVERB << "Test " << #x << ": " << info << std::endl;           \
        if( !(x) )                                                      \
        {                                                               \
            OUTPUT << #x << " failed: " << info << std::endl;           \
            ::exit( EXIT_FAILURE );                                     \
        }                                                               \
    }

namespace
{
class Watchdog : public lunchbox::Thread
{
public:
    Watchdog( const std::string& name ) : _name( name ) {}

    virtual void run()
        {
            lunchbox::Thread::setName( "Watchdog" );
#ifdef DASH_TEST_RUNTIME
            lunchbox::sleep( DASH_TEST_RUNTIME * 1000 );
            TESTINFO( false, 
                      "Watchdog triggered - " << _name <<
                      " did not terminate within " << DASH_TEST_RUNTIME << "s" );
#else
            lunchbox::sleep( 60000 );
            TESTINFO( false, 
                      "Watchdog triggered - " << _name <<
                      " did not terminate within 1 minute" );
#endif
        }

private:
    const std::string _name;
};
}

int main( int argc, char **argv )
{
#ifndef DASH_TEST_NO_WATCHDOG
    Watchdog watchdog( argv[0] );
    watchdog.start();
#endif

    const int result = dash::test::main( argc, argv );
    if( result != EXIT_SUCCESS )
        return result;

#ifndef DASH_TEST_NO_WATCHDOG
    watchdog.cancel();
    lunchbox::sleep( 10 ); // give watchdog time to terminate
#endif
    return EXIT_SUCCESS;
}

#endif // DASHTEST_TEST_H

