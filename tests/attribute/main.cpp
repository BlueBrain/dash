
// Copyright (c) 2011 EPFL/BBP. All rights reserved.
// Author: Stefan Eilemann

#include "test.h"

#include <dash/Context.h>
#include <dash/Attribute.h>
#include <co/co.h>

struct Foo
{
    int i;
};

struct Bar
{
    float f;
};

int dash::test::main( int argc, char **argv )
{
    dash::Context::getMain( argc, argv );
    //co::base::sleep( 5000 );

    dash::AttributePtr attr1 = new dash::Attribute( std::string( "hello" ));
    TEST( attr1->get< const std::string >() == "hello" );

    *attr1 = 42;
    TEST( attr1->get< const int >() == 42 );

    Foo foo;
    foo.i = 17;
    *attr1 = foo;

    {
        dash::Context auxCtx;
        //auxCtx.setCurrent();
        const Foo& fooRef = attr1->get< const Foo& >();
        TEST( fooRef.i == 17 );
        
        foo.i = 42;
        TEST( fooRef.i == 17 );

        attr1->get< Foo& >();
    }
    return EXIT_SUCCESS;
}
