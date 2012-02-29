
// Copyright (c) 2011 EPFL/BBP. All rights reserved.
// Author: Stefan Eilemann

#include "Commit.h"

#include "detail/Commit.h"

namespace dash
{
Commit::Commit()
        : impl_( new detail::Commit )
{}

Commit::Commit( const Commit& from )
        : impl_( from.impl_ )
{}

Commit& Commit::operator = ( const Commit& from )
{
    impl_ = from.impl_;
    return *this;
}

}
