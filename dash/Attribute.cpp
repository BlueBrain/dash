
// Copyright (c) 2011 EPFL/BBP. All rights reserved.
// Author: Stefan Eilemann

#include "Attribute.h"

#include "detail/Attribute.h"

namespace dash
{
Attribute::Attribute()
{
    init_();
}

Attribute::Attribute( const Attribute& from )
        : Referenced( from )
{
    impl_ = new detail::Attribute( this, from.impl_ );
    impl_->ref( CO_REFERENCED_PARAM );
}

void Attribute::init_()
{
    impl_ = new detail::Attribute( this );
    impl_->ref( CO_REFERENCED_PARAM );
}

Attribute::~Attribute()
{
    impl_->orphan();
    impl_->unref( CO_REFERENCED_PARAM );
}

Attribute& Attribute::operator = ( const Attribute& from )
{
    if( this == &from )
        return *this;
    *impl_ = *from.impl_;
    return *this;
}

Attribute& Attribute::set_( const boost::any& value )
{
    impl_->set( value );
    return *this;
}

boost::any& Attribute::get_()
{
    return impl_->get();
}

const boost::any& Attribute::get_() const
{
    return impl_->get();
}


}
