
/* Copyright (c) 2012, EPFL/Blue Brain Project
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

#ifndef DASH_DETAIL_SERIALIZABLE_H
#define DASH_DETAIL_SERIALIZABLE_H

#include <dash/api.h>

#pragma warning( push )
#pragma warning( disable: 4308 )
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#pragma warning( pop )

#pragma warning( push )
#pragma warning( disable: 4996 )
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#pragma warning( pop )


/** Provides generic serialization implementation for classes using a pimpl
    which is a lunchbox::Referenced. */
#define SERIALIZABLEREF( class, oarchive, iarchive )            \
    template<> DASH_API                                         \
    void class::save( oarchive& ar, const unsigned int ) const  \
    {                                                           \
        ar << impl_;                                            \
    }                                                           \
    template<> DASH_API                                         \
    void class::load( iarchive& ar, const unsigned int )        \
    {                                                           \
        impl_->orphan();                                        \
        impl_->unref( this );                                   \
        ar >> impl_;                                            \
        impl_->ref( this );                                     \
    }

/** Provides generic serialization implementation for classes using a pimpl. */
#define SERIALIZABLEPLAIN( class, oarchive, iarchive )          \
    template<> DASH_API                                         \
    void class::save( oarchive& ar, const unsigned int ) const  \
    {                                                           \
        ar << impl_;                                            \
    }                                                           \
    template<> DASH_API                                         \
    void class::load( iarchive& ar, const unsigned int )        \
    {                                                           \
        ar >> impl_;                                            \
    }

/** Provides serialization implementation with boost.textArchive using the
    given impl macro. */
#define SERIALIZABLETEXTARCHIVE( class, impl )  \
    impl( class, boost::archive::text_oarchive, boost::archive::text_iarchive )

/** Provides serialization implementation with boost.binaryArchive using the
    given impl macro. */
#define SERIALIZABLEBINARYARCHIVE( class, impl )    \
    impl( class, boost::archive::binary_oarchive,   \
                 boost::archive::binary_iarchive )

#endif // DASH_DETAIL_SERIALIZABLE_H
