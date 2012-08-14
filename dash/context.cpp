
/* Copyright (c) 2011-2012, EFPL/Blue Brain Project
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

#include "context.h"

#include <dash/attribute.h>
#include <dash/node.h>
#include <dash/version.h>

#include "detail/attribute.h"
#include "detail/commit.h"
#include "detail/context.h"

#include <lunchbox/init.h>
#include <pthread.h>
#include <lunchbox/perThread.h>
#include <lunchbox/version.h>


namespace dash
{
namespace
{
    void noDelete( Context* ) {}
    static Context* _mainContext = 0;
    lunchbox::PerThread< Context, &noDelete > _currentContext;
    static lunchbox::SpinLock* getInitLock_()
    {
        static lunchbox::SpinLock lock;
        return &lock;
    }
}

Context::Context()
        : impl_( new detail::Context )
{}

Context::~Context()
{
    LBASSERT( _mainContext );
    if( _currentContext == this )
        _currentContext = 0;

    delete impl_;
    LBASSERT( _currentContext != this );

    lunchbox::ScopedFastWrite mutex( getInitLock_( ));
    if( _mainContext == this )
    {
        _mainContext = 0;
        if( !lunchbox::exit( ))
            LBERROR << "Collage exit failed" << std::endl;
    }
}

Context& Context::getMain( const int argc, char** argv )
{
    lunchbox::ScopedFastWrite mutex( getInitLock_( ));
    if( !_mainContext )
    {
        LBASSERT( lunchbox::Version::check( ));
        if( !lunchbox::Version::check()  || !lunchbox::init( argc, argv ))
            LBERROR << "Lunchbox initialization failed" << std::endl;
        LBINFO << "Initializing main dash::Context v" << Version::getString()
               << std::boolalpha << std::endl;
        _mainContext = new Context;
    }
    else if( argc > 0 )
    {
        LBWARN << "Main context already initialized, ignoring command line "
               << "arguments" << std::endl;
        LBASSERT( argc == 0 );
    }
    return *_mainContext;
}

Context& Context::setCurrent()
{
    Context& previous = getCurrent();
    _currentContext = this;
    return previous;
}

Context& Context::getCurrent()
{
    // thread-local, therefore threadsafe
    // Do not restructure code without making sure you don't end up with
    // multiple pthread_getspecific calls (git blame this comment)
    Context* context = _currentContext.get();
    if( context )
        return *context;

    context = &getMain();
    _currentContext = context;
    return *context;
}

void Context::map( dash::NodePtr node, const Context& to )
{
    Context& current = setCurrent();
    impl_->map( node, *to.impl_ );
    current.setCurrent();
}

void Context::unmap( dash::NodePtr node )
{
    Context& current = setCurrent();
    impl_->unmap( node );
    current.setCurrent();
}

void Context::map( dash::AttributePtr attribute, const Context& to )
{
    Context& current = setCurrent();
    impl_->map( attribute->getImpl(), *to.impl_ );
    current.setCurrent();
}

void Context::unmap( dash::AttributePtr attribute )
{
    Context& current = setCurrent();
    impl_->unmap( attribute->getImpl( ));
    current.setCurrent();
}

Commit Context::commit()
{
    return impl_->commit();
}

void Context::apply( const Commit& cmt )
{
    Context& current = setCurrent(); // record applied changes in proper context
    impl_->apply( cmt.getImpl( ));
    current.setCurrent();
}

}
