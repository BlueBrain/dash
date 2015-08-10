
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

#include "test.h"

#include <dash/context.h>
#include <dash/attribute.h>

int main( int argc, char **argv )
{
    dash::Context& mainCtx = dash::Context::getMain( argc, argv );

    dash::AttributePtr attr1 = new dash::Attribute( 42 );

    {
        dash::Context auxCtx;
        mainCtx.map( attr1, auxCtx );

        TEST( attr1->get< int >() == 42 );

        auxCtx.setCurrent();
        *attr1 = 17;
        TEST( attr1->get< int >() == 17 );

        mainCtx.setCurrent();
        TEST( attr1->get< int >() == 42 );

        auxCtx.setCurrent();
        TEST( attr1->get< int >() == 17 );

        mainCtx.apply( auxCtx.commit( ));
        mainCtx.setCurrent();
        TESTINFO( attr1->get< int >() == 17, attr1->get< int >( ));
    }

    return EXIT_SUCCESS;
}
