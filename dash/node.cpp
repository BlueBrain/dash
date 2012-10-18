
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

#include "node.h"

#include "detail/childIterator.h"
#include "detail/node.h"
#include "detail/serializable.h"

namespace dash
{

SERIALIZABLETEXTARCHIVE( Node, SERIALIZABLEREF )
SERIALIZABLEBINARYARCHIVE( Node, SERIALIZABLEREF )

Node::Node()
    : Referenced()
#pragma warning( push )
#pragma warning( disable: 4355 )
    , impl_( new detail::Node( this ))
#pragma warning( pop )
{
    impl_->ref( this );
}

Node::Node( const Node& from )
        : Referenced( from )
#pragma warning( push )
#pragma warning( disable: 4355 )
        , impl_( new detail::Node( this, from.impl_ ))
#pragma warning( pop )
{
    impl_->ref( this );
}

Node::~Node()
{
    impl_->orphan();
    impl_->unref( this );
}

Node& Node::operator = ( const Node& from )
{
    if( this == &from )
        return *this;
    *impl_ = *from.impl_;
    return *this;
}

bool Node::operator == ( const Node& rhs ) const
{
    if( this == &rhs )
        return true;
    return *impl_ == *rhs.impl_;
}

namespace
{
template< class N, class A > inline
VisitorResult accept_( N* node, NodeVisitor< lunchbox::RefPtr< N >,
                                             lunchbox::RefPtr< A > >& visitor )
{
    switch( visitor.visitDown( node ))
    {
      case ACCEPT_CONTINUE: break;
      case ACCEPT_PRUNE: return visitor.visitUp( node );
      case ACCEPT_TERMINATE: return ACCEPT_TERMINATE;
    }

    for( detail::ChildIterator< N > i = node->childrenBegin();
         i < node->childrenEnd(); ++i )
    {
        switch( i->accept( visitor ))
        {
          case ACCEPT_CONTINUE: break;
          case ACCEPT_PRUNE: return visitor.visitUp( node );
          case ACCEPT_TERMINATE: return ACCEPT_TERMINATE;
        }
    }

    for( detail::AttributeIterator< N, A > i = node->attributesBegin();
         i < node->attributesEnd(); ++i )
    {
        switch( visitor.visit( *i ))
        {
          case ACCEPT_CONTINUE: break;
          case ACCEPT_PRUNE:
              return visitor.visitUp( node );
          case ACCEPT_TERMINATE: return ACCEPT_TERMINATE;
        }
    }
    return visitor.visitUp( node );
}
}

VisitorResult Node::accept( Visitor& visitor )
{
    return accept_< Node, Attribute >( this, visitor );
}

VisitorResult Node::accept( ConstVisitor& visitor ) const
{
    return accept_< const Node, const Attribute >( this, visitor );
}

// Hierarchy
void Node::insert( NodePtr child )
{
    impl_->insert( child );
}

void Node::erase( NodePtr child )
{
    impl_->erase( child );
}

bool Node::hasParents() const
{
    return impl_->hasParents();
}

size_t Node::getNParents() const
{
    return impl_->getNParents();
}

Node* Node::getParent( const size_t i )
{
    return impl_->getParent( i );
}

const Node* Node::getParent( const size_t i ) const
{
    return impl_->getParent( i );
}

Node::ConstParentIterator Node::parentsBegin() const
{
    return ConstParentIterator( this, 0 );
}

Node::ConstParentIterator Node::parentsEnd() const
{
    return ConstParentIterator( this, getNParents( ));
}

Node::ParentIterator Node::parentsBegin()
{
    return ParentIterator( this, 0 );
}

Node::ParentIterator Node::parentsEnd()
{
    return ParentIterator( this, getNParents( ));
}

size_t Node::getNChildren() const
{
    return impl_->getNChildren();
}

NodePtr Node::getChild( const size_t i )
{
    return impl_->getChild( i );
}

ConstNodePtr Node::getChild( const size_t i ) const
{
    return impl_->getChild( i );
}

Node::ConstChildIterator Node::childrenBegin() const
{
    return ConstChildIterator( this, 0 );
}

Node::ConstChildIterator Node::childrenEnd() const
{
    return ConstChildIterator( this, getNChildren( ));
}

Node::ChildIterator Node::childrenBegin()
{
    return ChildIterator( this, 0 );
}

Node::ChildIterator Node::childrenEnd()
{
    return ChildIterator( this, getNChildren( ));
}

// Attributes
void Node::insert( AttributePtr attribute )
{
    impl_->insert( attribute );
}

void Node::erase( AttributePtr attribute )
{
    impl_->erase( attribute );
}

size_t Node::getNAttributes() const
{
    return impl_->getNAttributes();
}

AttributePtr Node::getAttribute( const size_t i )
{
    return impl_->getAttribute( i );
}

ConstAttributePtr Node::getAttribute( const size_t i ) const
{
    return impl_->getAttribute( i );
}

Node::ConstAttributeIterator Node::attributesBegin() const
{
    return ConstAttributeIterator( this, 0 );
}

Node::ConstAttributeIterator Node::attributesEnd() const
{
    return ConstAttributeIterator( this, getNAttributes( ));
}

Node::AttributeIterator Node::attributesBegin()
{
    return AttributeIterator( this, 0 );
}

Node::AttributeIterator Node::attributesEnd()
{
    return AttributeIterator( this, getNAttributes( ));
}

}
