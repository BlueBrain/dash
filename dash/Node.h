
// Copyright (c) 2011 EPFL/BBP. All rights reserved.
// Author: Stefan Eilemann

#ifndef DASH_NODE_H
#define DASH_NODE_H

#include <dash/api.h>
#include <dash/types.h>
#include <dash/NodeVisitor.h>   // nested typedef
#include <dash/VisitorResult.h> // return value

#include <dash/detail/AttributeIterator.h> // return value
#include <dash/detail/ChildIterator.h>     // return value

#include <co/base/referenced.h> // base class

namespace dash
{
namespace detail { class Node; }

/**
 * A node of a dash graph.
 *
 * Nodes form directed acyclic graphs (DAG) in dash. They hold one or more
 * Attribute data items. All data access to a Node is thread-safe as long as it
 * happens with different contexts. Modifying a Node is not visible to other
 * contexts until a Commit is applied to the Context.
 *
 * Nodes are by default only visible in the Context they are constructed
 * in. They are made visible in other contexts using Context::map().
 */
class Node : public co::base::Referenced
{
public:
    /** Node tree visitor */
    typedef NodeVisitor< NodePtr, AttributePtr > Visitor;

    /** Const node tree visitor */
    typedef NodeVisitor< NodeConstPtr, AttributeConstPtr > ConstVisitor;

    /** An iterator over the attribute vector. */
    typedef detail::AttributeIterator< Node, Attribute > AttributeIterator;
    /** A const iterator over the attribute vector. */
    typedef detail::AttributeIterator< const Node,
                                       const Attribute > ConstAttributeIterator;

    /** An iterator over the child vector. */
    typedef detail::ChildIterator< Node > ChildIterator;
    /** A const iterator over the child vector. */
    typedef detail::ChildIterator< const Node > ConstChildIterator;

    DASH_API Node(); //!< Construct a new empty node. @version 0.1

    /** Construct a shallow, parent-less copy. @version 0.1 */
    DASH_API Node( const Node& from );

    DASH_API virtual ~Node(); //!< Destruct this node. @version 0.1

    /** Perform a shallow, parent-less copy. @version 0.1 */
    DASH_API Node& operator = ( const Node& from );

    /**
     * Traverse this node tree using the given visitor.
     *
     * @return the result of the last visit.
     * @version 1.0 
     */
    DASH_API VisitorResult accept( Visitor& visitor );

    /**
     * Traverse this const node tree using the given visitor.
     *
     * @return the result of the last visit.
     * @version 1.0 
     */
    DASH_API VisitorResult accept( ConstVisitor& visitor ) const;

    /** @name Node hierarchy */
    //@{
    /** Establish a relationship between the two nodes. @version 0.1 */
    DASH_API void insert( NodePtr child );

    /** Break the relationship between the two nodes. @version 0.1 */
    DASH_API void erase( NodePtr child );

    /** @return true of the Node has parents, false otherwise. @version 0.1 */
    DASH_API bool hasParents() const;

    /** @return the current number of parents. @version 0.1 */
    DASH_API size_t getNParents() const;

    /** @return the current number of children. @version 0.1 */
    DASH_API size_t getNChildren() const;

    /** @return the child at the given position. @version 0.1 */
    DASH_API NodePtr getChild( const size_t i );

    /** @return the child at the given position. @version 0.1 */
    DASH_API NodeConstPtr getChild( const size_t i ) const;

    /** @return an iterator pointing to the start of the children. @version 0.1*/
    DASH_API ConstChildIterator childrenBegin() const;

    /** @return an iterator pointing to the end of the children. @version 0.1*/
    DASH_API ConstChildIterator childrenEnd() const;

    /** @return an iterator pointing to the start of the children. @version 0.1*/
    DASH_API ChildIterator childrenBegin();

    /** @return an iterator pointing to the end of the children. @version 0.1*/
    DASH_API ChildIterator childrenEnd();
    //@}

    /** @name Attribute data storage */
    //@{
    /** Add an attribute to this node. @version 0.1 */
    DASH_API void insert( AttributePtr attribute );

    /** Remove an attribute from this node. @version 0.1 */
    DASH_API void erase( AttributePtr attribute );

    /** @return the current number of attributes. @version 0.1 */
    DASH_API size_t getNAttributes() const;

    /** @return the attribute at the given position. @version 0.1 */
    DASH_API AttributePtr getAttribute( const size_t i );

    /** @return the const attribute at the given position. @version 0.1 */
    DASH_API AttributeConstPtr getAttribute( const size_t i ) const;

    /** @return iterator pointing to the first attribute. @version 0.1*/
    DASH_API ConstAttributeIterator attributesBegin() const;

    /** @return iterator pointing to the end of the attributes. @version 0.1*/
    DASH_API ConstAttributeIterator attributesEnd() const;

    /** @return iterator pointing to the start of the attributes. @version 0.1*/
    DASH_API AttributeIterator attributesBegin();

    /** @return iterator pointing to the end of the attributes. @version 0.1*/
    DASH_API AttributeIterator attributesEnd();
    //@}

    /** @name Internal */
    //@{
    detail::Node* getImpl() { return impl_; } //!< @internal
    const detail::Node* getImpl() const { return impl_; } //!< @internal
    //@}

private:
    // use raw pointer instead of NodePtr to avoid leak of detail::Node
    detail::Node* impl_;
};

}

#endif // DASH_NODE_H
