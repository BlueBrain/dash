
// Copyright (c) 2011 EPFL/BBP. All rights reserved.
// Author: Stefan Eilemann

#include "test.h"
#include <dash/Context.h>

int dash::test::main( int argc, char **argv )
{
    TEST( &dash::Context::getMain( argc, argv ));
    TEST( &dash::Context::getCurrent( ));
    TEST( &dash::Context::getCurrent() == &dash::Context::getMain( ));

    return EXIT_SUCCESS;
}
