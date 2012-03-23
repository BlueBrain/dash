
/* Copyright (c) 2011, EFPL/Blue Brain Project
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

#ifndef DASH_COMMIT_H
#define DASH_COMMIT_H

#include <dash/api.h>
#include <dash/types.h>
#include <dash/Serializable.h>

namespace dash
{

/**
 * A set of changes emitted by a Context.
 *
 * Each Context::commit() generates a new set of changes containing all data
 * modified since the last commit. This Commit can be applied to another
 * Context.
 */
class Commit
{
public:
    /** Create a copy of a commit. @version 0.1 */
    DASH_API Commit( const Commit& from );

    /** Destruct this commit. @version 0.1 */
    DASH_API ~Commit(){}

    /** Assign the changes from another commit. @version 0.1 */
    DASH_API Commit& operator = ( const Commit& from );

    /** Check this Commit on equality. @version 0.1 */
    DASH_API bool operator == ( const Commit& rhs ) const;

    /** Check this Commit on equality. @version 0.1 */
    DASH_API bool operator != ( const Commit& rhs ) const
        { return !(*this == rhs); }

    /** @name Internal */
    //@{
    /** @internal Create a new, empty commit. */
    Commit();
    detail::CommitPtr getImpl() { return impl_; } //!< @internal
    detail::CommitConstPtr getImpl() const { return impl_; } //!< @internal
    //@}

private:
    SERIALIZABLE()

    detail::CommitPtr impl_;
};

}

#endif // DASH_COMMIT_H
