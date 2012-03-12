
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

#ifndef DASH_SERIALIZABLE_H
#define DASH_SERIALIZABLE_H

#include <boost/serialization/access.hpp>
#include <boost/serialization/split_member.hpp>

//! Declares a class to be serializable wrt boost.serialization.
#define SERIALIZABLE()                                          \
    friend class boost::serialization::access;                  \
    template<class Archive>                                     \
    void save( Archive& ar, const unsigned int version ) const; \
    template<class Archive>                                     \
    void load( Archive& ar, const unsigned int version );       \
    BOOST_SERIALIZATION_SPLIT_MEMBER()

//! Provides default serialization implementation for classes using a pimpl.
#define SERIALIZABLEIMPL( class, oarchive, iarchive )                   \
    template<>                                                          \
    void class::save( oarchive& ar, const unsigned int version ) const  \
    {                                                                   \
        ar << *getImpl();                                               \
    }                                                                   \
    template<>                                                          \
    void class::load( iarchive& ar, const unsigned int version )        \
    {                                                                   \
        ar >> *getImpl();                                               \
    }

#endif // DASH_SERIALIZABLE_H
