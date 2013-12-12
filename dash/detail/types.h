
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

#ifndef DASH_DETAIL_TYPES_H
#define DASH_DETAIL_TYPES_H

#include <dash/types.h>
#include <lunchbox/any.h>
#include <lunchbox/lfVector.h>
#include <vector>


namespace dash
{
namespace test
{
int main( int argc, char **argv ); //!< @internal
}

namespace detail
{

class ContextCommit;

template< class T > class ContextPtr;

class CommitChange;
typedef LFVector< CommitChange, 32 > CommitChanges;
typedef CommitChanges::iterator ChangesIter;
typedef CommitChanges::const_iterator ChangesCIter;

class ContextChange;
typedef LFVector< ContextChange, 32 > ContextChanges;

class Node;
typedef lunchbox::RefPtr< Node > NodePtr;
typedef lunchbox::RefPtr< const Node > ConstNodePtr;

typedef std::vector< Node* > Parents;
typedef Parents::iterator ParentsIter;
typedef Parents::const_iterator ParentsCIter;
typedef ContextPtr< Parents > ParentsCtxPtr;

typedef std::vector< dash::NodePtr > Children;
typedef Children::iterator ChildrenIter;
typedef Children::const_iterator ChildrenCIter;
typedef ContextPtr< Children > ChildrenCtxPtr;

class Attribute;
typedef lunchbox::RefPtr< Attribute > AttributePtr;
typedef lunchbox::RefPtr< const Attribute > ConstAttributePtr;
typedef Attributes::iterator AttributesIter;
typedef Attributes::const_iterator AttributesCIter;
typedef ContextPtr< dash::Attributes > AttributesCtxPtr;

typedef ContextPtr< lunchbox::Any > AnyCtxPtr;
}
}

#endif // DASH_DETAIL_TYPES_H
