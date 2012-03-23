
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

#include "Context.h"

#include <dash/Attribute.h>
#include <dash/Node.h>
#include <dash/Version.h>

#include "detail/Attribute.h"
#include "detail/Commit.h"
#include "detail/Context.h"

#include <lunchbox/init.h>
#include <lunchbox/perThread.h>
#include <lunchbox/version.h>

#ifdef _MSC_VER
#  define THREAD_LOCAL( T, N ) __declspec( thread ) T* N = 0
#elif defined __APPLE__
#  define THREAD_LOCAL( T, N )                              \
    co::base::PerThread< T, co::base::perThreadNoDelete > N
#else // gcc
#  define THREAD_LOCAL( T, N ) __thread T* N = 0
#endif

namespace dash
{
namespace
{
    static Context* _mainContext = 0;
    THREAD_LOCAL( Context, _currentContext );
    static co::base::SpinLock* getInitLock_()
    {
        static co::base::SpinLock lock;
        return &lock;
    }
}

Context::Context()
        : impl_( new detail::Context )
{}

Context::~Context()
{
    EQASSERT( _mainContext );
    if( _currentContext == this )
        _currentContext = 0;

    delete impl_;
    EQASSERT( _currentContext != this );

    co::base::ScopedFastWrite mutex( getInitLock_( ));
    if( _mainContext == this )
    {
        _mainContext = 0;
        if( !co::base::exit( ))
            EQERROR << "Collage exit failed" << std::endl;
    }
}

Context& Context::getMain( const int argc, char** argv )
{
    co::base::ScopedFastWrite mutex( getInitLock_( ));
    if( !_mainContext )
    {
        EQASSERT( lunchbox::Version::check( ));
        if( !lunchbox::Version::check()  || !co::base::init( argc, argv ))
            EQERROR << "Collage initialization failed" << std::endl;
        EQINFO << "Initializing main dash::Context v" << Version::getString()
               << std::boolalpha << std::endl;
        _mainContext = new Context;
    }
    else if( argc > 0 )
    {
        EQWARN << "Main context already initialized, ignoring command line "
               << "arguments" << std::endl;
        EQASSERT( argc == 0 );
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
    if( !_currentContext )
        _currentContext = &getMain();
    return *_currentContext;
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
