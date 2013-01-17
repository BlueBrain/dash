
/* Copyright (c) 2011-2012, EPFL/Blue Brain Project
 *                          Stefan.Eilemann@epfl.ch
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

#ifndef DASH_ATTRIBUTE_H
#define DASH_ATTRIBUTE_H

#include <dash/api.h>
#include <dash/types.h>
#include <lunchbox/serializable.h>

#include <lunchbox/referenced.h> // base class
#include <lunchbox/any.h> // used inline

namespace dash
{
namespace detail { class Attribute; }

/**
 * An attribute of a dash Node.
 *
 * Attributes store data in the DAG formed by nodes. All data access to an
 * Attribute is thread-safe as long as it happens from different contexts.
 * Modifying an Attribute is not visible to other contexts until a Commit is
 * applied to the Context.
 *
 * Attributes are by default only visible in the Context they are constructed
 * in. They are made visible in other contexts using Context::map().
 */
class Attribute : public lunchbox::Referenced
{
public:
    DASH_API Attribute(); //!< Construct a new empty attribute. @version 0.1

    /** Construct a shallow, parent-less copy. @version 0.1 */
    DASH_API Attribute( const Attribute& from );

    /** Construct a new attribute with a default value. @version 0.1 */
    template< class T > Attribute( const T& value ){ init_(); (*this) = value; }

    DASH_API virtual ~Attribute(); //!< Destruct this attribute. @version 0.1

    /** Perform a shallow, parent-less assignment. @version 0.1 */
    DASH_API Attribute& operator = ( const Attribute& from );

    /** Assign a value to this Attribute. @version 0.1 */
    template< class T > Attribute& operator = ( const T& rhs )
        { return set_( lunchbox::Any( rhs )); }

    /** Check this Attribute on equality. @version 0.1 */
    DASH_API bool operator == ( const Attribute& rhs ) const;

    /** Check this Attribute on inequality. @version 0.1 */
    DASH_API bool operator != ( const Attribute& rhs ) const
        { return !(*this == rhs); }

    /** Set a new value to this Attribute. @version 0.1 */
    template< class T > void set( const T& value )
        { set_( lunchbox::Any( value )); }

    /**
     * @return the stored value for modification.
     * @throws lunchbox::bad_any_cast.
     * @version 0.1
     */
    template< class T > T getMutable()
        { return lunchbox::any_cast< T >( getMutable_( )); }

    /** @return the stored value without checking the type. @version 0.1 */
    template< class T > T getMutableUnsafe()
        { return lunchbox::unsafe_any_cast< T >( getMutable_( )); }

    /**
     * @return the stored value.
     * @throws lunchbox::bad_any_cast.
     * @version 0.1
     */
    template< class T > const T get() const
        { return lunchbox::any_cast< T >( get_( )); }

    /** @return the stored value without checking the type. @version 0.1 */
    template< class T > const T getUnsafe() const
        { return lunchbox::unsafe_any_cast< const T >( get_( )); }

    /** @name Internal */
    //@{
    detail::Attribute* getImpl() { return impl_; } //!< @internal
    const detail::Attribute* getImpl() const { return impl_; } //!< @internal
    //@}

private:
    LB_SERIALIZABLE

    detail::Attribute* impl_;

    DASH_API void init_();
    DASH_API Attribute& set_( const lunchbox::Any& value );
    DASH_API lunchbox::Any& getMutable_();
    DASH_API const lunchbox::Any& get_() const;
};

}

#endif // DASH_ATTRIBUTE_H
