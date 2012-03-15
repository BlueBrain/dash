
/* Copyright (c) 2012, EFPL/Blue Brain Project
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

#ifndef DASH_CO_SERIALIZATION_H
#define DASH_CO_SERIALIZATION_H

#include <co/types.h>
#include <co/object.h>
#include <co/dataOStream.h>
#include <co/dataIStream.h>
#include <co/dataOStreamArchive.h>
#include <co/dataIStreamArchive.h>

#include <dash/detail/AnySerialization.h>


SERIALIZABLEANY( co::uint128_t )


namespace dash
{

/**
 * Namespace providing functionality to distributed dash object through the
 * Collage library.
 */
namespace cash
{

/** */
template< class T >
class Distributable : public co::Object
{
public:
    typedef co::base::RefPtr< T > ValuePtr;

    Distributable()
        : value_( new T )
    {}

    Distributable( ValuePtr value )
        : value_( value )
    {}

    ValuePtr getValue() const
    {
        return value_;
    }

protected:
    virtual void getInstanceData( co::DataOStream& os )
    {
        dash::detail::serializeAny< co::DataOStreamArchive >( *value_, os );
    }

    virtual void applyInstanceData( co::DataIStream& is )
    {
        dash::detail::serializeAny< co::DataIStreamArchive >( *value_, is );
    }

private:
    ValuePtr value_;
};

} // co
} // dash

#endif
