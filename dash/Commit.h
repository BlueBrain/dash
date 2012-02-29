
// Copyright (c) 2011 EPFL/BBP. All rights reserved.
// Author: Stefan Eilemann

#ifndef DASH_COMMIT_H
#define DASH_COMMIT_H

#include <dash/api.h>
#include <dash/types.h>

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

    /** @name Internal */
    //@{
    /** @internal Create a new, empty commit. */
    Commit();
    detail::CommitPtr getImpl() { return impl_; } //!< @internal
    detail::CommitConstPtr getImpl() const { return impl_; } //!< @internal
    //@}

private:
    detail::CommitPtr impl_;
};

}

#endif // DASH_COMMIT_H
