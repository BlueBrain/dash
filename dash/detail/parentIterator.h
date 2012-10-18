
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

#ifndef DASH_DETAIL_PARENT_ITERATOR_H
#define DASH_DETAIL_PARENT_ITERATOR_H

#include <lunchbox/indexIterator.h>

namespace dash
{
namespace detail
{

template< class T >
class ParentIterator : public lunchbox::IndexIterator< ParentIterator< T >, T, T >
{
    typedef lunchbox::IndexIterator< ParentIterator< T >, T, T > Super;

public:
    ParentIterator() : Super( 0, 0 ) {}
    ParentIterator( T* node, size_t i ) : Super( node, i ) {}
    template< class U >
    ParentIterator( const ParentIterator< U >& from ) : Super( from ) {}

    T* operator*() const { return Super::container_->getParent( Super::i_ )->getNode( ); }
    T* operator[]( const size_t& n ) const
        { return Super::container_->getParent( Super::i_ + n )->getNode( ); }

private:
    //template< class, int32_t > friend class Child; // Child::erase
};

}
}

#endif // DASH_DETAIL_PARENT_ITERATOR_H
