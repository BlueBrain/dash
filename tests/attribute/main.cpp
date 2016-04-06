
/* Copyright (c) 2011-2012, EPFL/Blue Brain Project
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

#include <lunchbox/test.h>

#include <dash/context.h>
#include <dash/attribute.h>

struct Foo
{
    int i;

    bool operator == ( const Foo& rhs ) const
    {
        if( this == &rhs )
            return true;
        return i == rhs.i;
    }
};

int main( int argc, char **argv )
{
    dash::Context::getMain( argc, argv );

    dash::AttributePtr attr1 = new dash::Attribute( std::string( "hello" ));
    TEST( attr1->get< const std::string >() == "hello" );

    *attr1 = 42;
    TEST( attr1->get< const int >() == 42 );

    Foo foo;
    foo.i = 17;
    *attr1 = foo;

    {
        dash::Context auxCtx;
        const Foo& fooRef = attr1->get< const Foo& >();
        TEST( fooRef.i == 17 );

        foo.i = 42;
        TEST( fooRef.i == 17 );

        attr1->getMutable< Foo& >();
    }

    *attr1 = static_cast< const Foo* >( &foo );
    const Foo* fooPtr = attr1->get< const Foo* >();
    TESTINFO( fooPtr->i == 42, fooPtr->i );

    return EXIT_SUCCESS;
}
