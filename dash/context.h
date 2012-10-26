
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

#ifndef DASH_CONTEXT_H
#define DASH_CONTEXT_H

#include <dash/commit.h> // return type
#include <dash/api.h>
#include <dash/types.h>

namespace dash
{
namespace detail { class Context; }

/**
 * The contextual view on the data.
 *
 * The Context provides an isolated view on data. Each thread can have a
 * different context and multiple threads may use the same context.
 *
 * Read and write access to Node and Attribute from multiple contexts is
 * thread-safe. Access from multiple threads using the same context to a
 * concrete Node or Attribute instance is not thread-safe. Writes are only
 * visible to the current context. They are propagated to child contexts using
 * Context::commit() and applied to a concrete child context using
 * Context::sync(). The commit and sync operation are thread-safe with any
 * operation in another context, but not thread-safe with operations on the same
 * context.
 */
class Context
{
public:
    /** @name Context management */
    //@{
    /**
     * Get the root context.
     *
     * Command line arguments are used only if this method is called before any
     * other dash call. Otherwise, dash will initialize the main context with
     * default values.
     *
     * @param argc the command line argument count.
     * @param argv the command line argument values.
     * @return the root context.
     * @version 0.1
     */
    DASH_API static Context& getMain( const int argc = 0, char** argv = 0 );

    /**
     * Create an auxiliary context.
     *
     * Does not change the current context. Note that there is always a main
     * context usable by the application.
     *
     * @version 0.1
     */
    DASH_API Context();

    /**
     * Destroy the given context.
     *
     * The context has not to be current in any thread anymore. DASH does not
     * check this, destroying a current context has undefined behaviour.
     *
     * Destroying the main context has to be done after all dash objects,
     * including non-main contexts and all commits, have been
     * released. Subsequent dash calls will cause re-initialization of the main
     * context.
     *
     * @version 0.1
     */
    DASH_API ~Context();

    /**
     * Set the context for the current thread.
     *
     * One context may be current in multiple threads. Concurrent access to a
     * single context is not thread-safe.
     *
     * @return the previous context.
     * @version 0.1
     */
    DASH_API Context& setCurrent();

    /**
     * Get the current context.
     *
     * If no current context is set, the main context will be made current and
     * returned as a result.
     *
     * @return the current context.
     * @version 0.1
     */
    DASH_API static Context& getCurrent();
    //@}

    /** @name Data visibility */
    //@{
    /**
     * Map the given node and all children from this context to the to context.
     *
     * Traverses the node tree and synchronizes the view from the from context
     * to this context. The from context need to have no pending changes, that
     * is, it should be fully committed. Not thread-safe with any other
     * operation on this or the from context.
     *
     * @param node the tree to map.
     * @param to the context to make the node visible in.
     * @version 0.1
     */
    DASH_API void map( dash::NodePtr node, const Context& to );

    /**
     * Release all references of the node tree in this context.
     *
     * Resets the view of this context. Used to release copies held by this
     * context for all nodes and attributes of the given node tree. Accessing
     * the node, or any of its children, after unmapping it results in undefined
     * behaviour.
     *
     * @param node the tree to unmap.
     * @version 0.1
     */
    DASH_API void unmap( dash::NodePtr node );

    /**
     * Map the given attribute from this context to the 'to' context.
     *
     * Synchronizes the view from the from context to this context. The from
     * context need to have no pending changes, that is, it should be fully
     * committed. Not thread-safe with any other operation on this or the from
     * context.
     *
     * @param attribute the tree to map.
     * @param to the context to make the attribute visible in.
     * @version 0.1
     */
    DASH_API void map( dash::AttributePtr attribute, const Context& to );

    /**
     * Release all references of the attribute in this context.
     *
     * Resets the view of this context. Used to release copies held by this
     * context for the attribute. Accessing the attribute, or any of its
     * children, after unmapping it results in undefined behaviour.
     *
     * @param attribute the tree to unmap.
     * @version 0.1
     */
    DASH_API void unmap( dash::AttributePtr attribute );
    //@}

    /** @name Versioning */
    //@{
    /**
     * Return the changes since the last commit.
     *
     * Not thread-safe with any other dash operation using this context, i.e.,
     * any other thread using this context should be idle.
     *
     * @return the change list.
     * @version 0.1
     */
    DASH_API Commit commit();

    /**
     * Apply a change set to this context.
     *
     * Not thread-safe with any other dash operation using this context, i.e.,
     * any other thread using this context should be idle.
     *
     * @param commit the change list.
     * @version 0.1
     */
    DASH_API void apply( const Commit& commit );
    //@}

    /** @name Internal */
    //@{
    detail::Context& getImpl() { return *impl_; } //!< @internal
    //@}

private:
    detail::Context* const impl_;

    Context( const Context& from ); //!< disable copy

    Context& operator = ( const Context& from ); // disable assignment
};

}

#endif // DASH_CONTEXT_H
