
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
#include "serialize.h"

#include <dash/Vector.h>


int dash::test::main( int argc, char **argv )
{
    dash::Vector< int > intVector;
    intVector.push_back( 0 );
    intVector.push_back( -7 );
    intVector.push_back( 42 );
    textSerializeAndTest( intVector );

    dash::Vector< float > floatVector;
    floatVector.push_back( 1.7f );
    floatVector.push_back( -8.2f );
    floatVector.push_back( 3.667f );
    textSerializeAndTest( floatVector );

    dash::Vector< std::string > stringVector;
    stringVector.push_back( "bla" );
    stringVector.push_back( "blub" );
    stringVector.push_back( "tralala" );
    textSerializeAndTest( stringVector );

    dash::Vector< Foo > fooVector;
    Foo foo1 = {42, 1.5f, false, "blablub"};
    Foo foo2 = {445, 41.2f, true, "foobar"};
    Foo foo3 = {-992, 0.56f, false, "12345qwert"};
    fooVector.push_back( foo1 );
    fooVector.push_back( foo2 );
    fooVector.push_back( foo3 );
    textSerializeAndTest( fooVector );

    return EXIT_SUCCESS;
}
