
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

#include <dash/Attribute.h>


int dash::test::main( int argc, char **argv )
{
    dash::AttributePtr outAttribute = new dash::Attribute;

    dash::AttributePtr intAttribute = new dash::Attribute( 42 );
    textSerialize( *intAttribute, *outAttribute );
    TEST( intAttribute->get<int>() == outAttribute->get<int>( ))
    binarySerialize( *intAttribute, *outAttribute );
    TEST( intAttribute->get<int>() == outAttribute->get<int>( ))

    dash::AttributePtr floatAttribute = new dash::Attribute( 42.f );
    textSerialize( *floatAttribute, *outAttribute );
    TEST( floatAttribute->get<float>() == outAttribute->get<float>( ))

    dash::AttributePtr stringAttribute =
                                     new dash::Attribute( std::string( "bla" ));
    textSerialize( *stringAttribute, *outAttribute );
    TEST( stringAttribute->get<std::string>() ==
          outAttribute->get<std::string>( ))

    dash::AttributePtr uint128Attribute =
                      new dash::Attribute( lunchbox::uint128_t( 12345, 54321 ));
    textSerialize( *uint128Attribute, *outAttribute );
    TEST( uint128Attribute->get<lunchbox::uint128_t>() ==
          outAttribute->get<lunchbox::uint128_t>( ))

    Foo foo = {42, 1.5f, false, "blablub"};
    dash::AttributePtr fooAttribute = new dash::Attribute( foo );
    textSerialize( *fooAttribute, *outAttribute );
    const Foo& outFoo = outAttribute->get<Foo>();
    TEST( foo.i == outFoo.i );
    TEST( foo.f == outFoo.f );
    TEST( foo.b == outFoo.b );
    TEST( foo.s == outFoo.s );

    return EXIT_SUCCESS;
}
