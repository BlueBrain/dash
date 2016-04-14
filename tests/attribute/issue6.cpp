
/* Copyright (c) 2011-2012, EPFL/Blue Brain Project
 *                          Daniel.Nachbaur@epfl.ch
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

#include <dash/attribute.h>
#include <dash/context.h>
#include <dash/node.h>

#include <dash/detail/commit.h>
#include <dash/detail/context.h>
#include <dash/detail/node.h>

int main( int argc, char **argv )
{
    dash::Context& mainCtx = dash::Context::getMain( argc, argv );

    typedef std::vector< int > DataType;
    dash::AttributePtr attr1 = new dash::Attribute( DataType( 10000, 0 ));

    {
        dash::Context auxCtx;
        mainCtx.map( attr1, auxCtx );
        auxCtx.setCurrent();

        for( int i = 0; i < 10000; ++i )
        {
            DataType& data = attr1->getMutable< DataType& >();
            data[0] = i+1;
        }

        mainCtx.apply( auxCtx.commit( ));

        mainCtx.setCurrent();
        TEST( attr1->get< const DataType& >()[0] == 10000 );
    }

    TEST( mainCtx.getImpl().commit_.contextChanges_.size() == 1 );
    mainCtx.commit();
    delete &mainCtx;

    return EXIT_SUCCESS;
}
