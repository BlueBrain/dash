
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
#include "node.h"

#include <dash/Node.h>
#include <dash/Attribute.h>


int dash::test::main( int argc, char **argv )
{
    dash::NodePtr root = createSampleNode();

    dash::NodePtr outRoot = new dash::Node;

    textSerialize( *root, *outRoot );
    TEST( areEqual( root, outRoot ));

    binarySerialize( *root, *outRoot );
    TEST( areEqual( root, outRoot ));

    return EXIT_SUCCESS;
}
