
/* Copyright (c) 2011-2012, EPFL/Blue Brain Project
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

#ifndef DASH_DETAIL_NODE_H
#define DASH_DETAIL_NODE_H

#include "contextPtr.h" // member (Nodes)
#include "contextPtr.h" // member (Nodes)
#include <dash/attribute.h> // AttributePtr return value
#include <lunchbox/referenced.h> // base class

#include <boost/serialization/vector.hpp>

namespace dash
{
namespace detail
{

/** The node implementation. */
class Node : public lunchbox::Referenced, public lunchbox::NonCopyable
{
public:
    explicit Node( dash::Node* node );
    Node( dash::Node* node, NodePtr from );
    DASH_API ~Node();

    Node& operator = ( const Node& from );

    bool operator == ( const Node& rhs ) const;
    bool operator != ( const Node& rhs ) const { return !(*this == rhs); }

    /** Set up a new slot for the node. */
    void map( const Context& from, const Context& to );
    /** Release references held by the context. */
    void unmap( Context& context );
    /** @return true if the Node is mapped to the context. */
    bool isMapped( const Context& context = Context::getCurrent( )) const;

    void orphan() { node_ = 0; } //!< Released by parent dash::Node

    /** @name Hierarchy */
    //@{
    bool hasParents() const { return !parents_->empty(); }
    size_t getNParents() const { return parents_->size(); }

    size_t getNChildren() const { return children_->size(); }
    dash::NodePtr getChild( const size_t i )
        { return (*static_cast< const Node * >( this )->children_)[ i ]; }
    dash::ConstNodePtr getChild( const size_t i ) const
        { return (*children_)[ i ]; }

    dash::Node* getParent( const size_t i )
    { return ((*static_cast< const Node * >( this )->parents_)[i])->getNode(); }
    const dash::Node* getParent( const size_t i ) const
        { return ((*parents_)[ i ])->getNode(); }

    void insert( dash::NodePtr child );
    bool erase( dash::NodePtr child );
    //@}

    /** @name Attributes */
    //@{
    size_t getNAttributes() const { return attributes_->size(); }
    dash::AttributePtr getAttribute( const size_t i )
        { return (*static_cast< const Node * >( this )->attributes_)[ i ]; }
    dash::ConstAttributePtr getAttribute( const size_t i ) const
        { return (*attributes_)[ i ]; }

    void insert( dash::AttributePtr attribute );
    bool erase( dash::AttributePtr attribute );
    //@}

    dash::Node* getNode() { return node_; }
    const dash::Node* getNode() const { return node_; }

private:
    LB_SERIALIZABLE

    friend int test::main( int argc, char **argv );
    dash::Node* node_;
    ParentsCtxPtr parents_;
    ChildrenCtxPtr children_;
    AttributesCtxPtr attributes_;

    Node() {}
};

template< class Archive >
inline void Node::save( Archive& ar, const unsigned int ) const
{
    ar << node_;
    ar << parents_.get();
    ar << children_.get();
    ar << attributes_.get();
}

template< class Archive >
inline void Node::load( Archive& ar, const unsigned int )
{
    ar >> node_;
    boost::shared_ptr< Parents > parents( new Parents );
    ar >> *parents;
    boost::shared_ptr< Children > children( new Children );
    ar >> *children;
    boost::shared_ptr< dash::Attributes > attributes( new dash::Attributes );
    ar >> *attributes;

    parents_.apply( parents );
    children_.apply( children );
    attributes_.apply( attributes );
}

}
}

#endif // DASH_DETAIL_NODE_H
