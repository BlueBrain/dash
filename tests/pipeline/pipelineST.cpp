
// Copyright (c) 2011 EPFL/BBP. All rights reserved.
// Author: Ahmet Bilgili

#include "test.h"

#include <dash/Context.h>
#include <dash/Attribute.h>

#define START_VALUE 100
#define STEP1_VALUE 50
#define STEP2_VALUE 500


int dash::test::main( int argc, char **argv )
{
    int currentVal = START_VALUE;

    dash::Context& mainCtx = dash::Context::getMain( argc, argv );
    dash::AttributePtr attr = new dash::Attribute( currentVal );

    Context ctx;

    mainCtx.map(attr, ctx);

    // First iteration
    int previousValue = currentVal;
    currentVal = STEP1_VALUE;
    *attr = currentVal;

    int value = static_cast< dash::AttributeConstPtr >( attr )->get<int>();
    TESTINFO( value == currentVal, value << "!=" << currentVal);

    Commit commit = mainCtx.commit();

    ctx.setCurrent();
    value = static_cast< dash::AttributeConstPtr >( attr )->get<int>();
    TESTINFO( value == previousValue, value << "!=" << previousValue );

    ctx.apply(commit);
    value = static_cast< dash::AttributeConstPtr >( attr )->get<int>();
    TESTINFO( value == currentVal, value << "!=" << currentVal);

    previousValue = currentVal;
    currentVal = STEP2_VALUE;

    // Second iteration
    mainCtx.setCurrent();
    *attr = currentVal;

    value = static_cast< dash::AttributeConstPtr >( attr )->get<int>();
    TESTINFO( value == currentVal, value << "!=" << currentVal);

    commit = mainCtx.commit();

    ctx.setCurrent();

    value = static_cast< dash::AttributeConstPtr >( attr )->get<int>();
    TESTINFO( value == previousValue, value  << "!=" << previousValue);

    ctx.apply(commit);

    value = static_cast< dash::AttributeConstPtr >( attr )->get<int>();
    TESTINFO( value == currentVal, value << "!=" << currentVal);

    return EXIT_SUCCESS;
}
