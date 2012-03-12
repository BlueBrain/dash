
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

#include "test.h"

#include <fstream>

#include <dash/Vector.h>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

# if defined __GNUC__
#  pragma GCC diagnostic ignored "-Warray-bounds"   // see comment below why
# endif

namespace
{
    template< typename T >
    bool isEqual( const dash::Vector<T>& v1, const dash::Vector<T>& v2 )
    {
        if( v1.size() != v2.size() )
            return false;

        for( size_t i = 0; i < v1.size(); ++i )
        {
            // this one causes an 'array subscript is below array bounds'
            // warning with gcc 4.5. Could be related to something like this:
            // http://gcc.gnu.org/bugzilla/show_bug.cgi?id=44848
            if( v1[i] != v2[i] )
                return false;
        }

        return true;
    }

    template< typename T >
    void saveVector( const dash::Vector<T>& vector )
    {
        std::ofstream ofs( "filename" );
        boost::archive::text_oarchive oarchive( ofs );
        oarchive << vector;
        ofs.close();
    }

    template< typename T >
    void loadVector( dash::Vector<T>& vector )
    {
        std::ifstream ifs("filename");
        boost::archive::text_iarchive iarchive( ifs );
        iarchive >> vector;
        ifs.close();
    }

    template< typename T >
    void serializeAndTest( const dash::Vector<T>& vector )
    {
        saveVector( vector );
        dash::Vector<T> loadedVector;
        loadVector( loadedVector );
        TEST( isEqual( vector, loadedVector ) );
    }
}


int dash::test::main( int argc, char **argv )
{
    dash::Vector< int > intVector;
    intVector.push_back( 0 );
    intVector.push_back( -7 );
    intVector.push_back( 42 );
    serializeAndTest( intVector );

    dash::Vector< float > floatVector;
    floatVector.push_back( 1.7f );
    floatVector.push_back( -8.2f );
    floatVector.push_back( 3.667f );
    serializeAndTest( floatVector );

    dash::Vector< std::string > stringVector;
    stringVector.push_back( "bla" );
    stringVector.push_back( "blub" );
    stringVector.push_back( "tralala" );
    serializeAndTest( stringVector );

    return EXIT_SUCCESS;
}
