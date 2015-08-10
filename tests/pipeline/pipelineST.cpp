
/* Copyright (c) 2011, EPFL/Blue Brain Project
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

#define START_VALUE 100
#define STEP1_VALUE 50
#define STEP2_VALUE 500

int main( int argc, char **argv )
{
    int currentVal = START_VALUE;

    dash::Context& mainCtx = dash::Context::getMain( argc, argv );
    dash::AttributePtr attr = new dash::Attribute( currentVal );
    dash::Context ctx;

    mainCtx.map( attr, ctx );

    // First iteration
    int previousValue = currentVal;
    currentVal = STEP1_VALUE;
    *attr = currentVal;

    int value = static_cast< dash::ConstAttributePtr >( attr )->get<int>();
    TESTINFO( value == currentVal, value << "!=" << currentVal);

    dash::Commit commit = mainCtx.commit();

    ctx.setCurrent();
    value = static_cast< dash::ConstAttributePtr >( attr )->get<int>();
    TESTINFO( value == previousValue, value << "!=" << previousValue );

    ctx.apply(commit);
    value = static_cast< dash::ConstAttributePtr >( attr )->get<int>();
    TESTINFO( value == currentVal, value << "!=" << currentVal);

    previousValue = currentVal;
    currentVal = STEP2_VALUE;

    // Second iteration
    mainCtx.setCurrent();
    *attr = currentVal;

    value = static_cast< dash::ConstAttributePtr >( attr )->get<int>();
    TESTINFO( value == currentVal, value << "!=" << currentVal);

    commit = mainCtx.commit();

    ctx.setCurrent();

    value = static_cast< dash::ConstAttributePtr >( attr )->get<int>();
    TESTINFO( value == previousValue, value  << "!=" << previousValue);

    ctx.apply(commit);

    value = static_cast< dash::ConstAttributePtr >( attr )->get<int>();
    TESTINFO( value == currentVal, value << "!=" << currentVal);

    ctx.commit();   // consume remaining changes

    return EXIT_SUCCESS;
}
