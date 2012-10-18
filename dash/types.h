
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

/**
 * @file dash/types.h
 *
 * Forward declarations and type definitions for the dash namespace.
 */
#ifndef DASH_TYPES_H
#define DASH_TYPES_H

#include <lunchbox/refPtr.h>
#include <lunchbox/types.h>
#include <lunchbox/uint128_t.h>

#include <vector>
#include <boost/shared_ptr.hpp>

namespace dash
{
using lunchbox::uint128_t;
using lunchbox::RefPtr;
using lunchbox::LFVector;

class Commit;
class Context;

class Attribute;
typedef RefPtr< Attribute > AttributePtr; //!< Attribute smart pointer
typedef RefPtr< const Attribute > ConstAttributePtr; //!< Attribute const pointer
typedef std::vector< AttributePtr > Attributes; //!< Vector of AttributePtr
/** Const iterator for Attributes */
typedef Attributes::const_iterator AttributesCIter;
typedef Attributes::iterator AttributesIter; //!< Iterator for Attributes

class Node;
typedef lunchbox::RefPtr< Node > NodePtr; //!< Node smart pointer
typedef lunchbox::RefPtr< const Node > ConstNodePtr; //!< Node const pointer
typedef std::vector< NodePtr > Nodes; //!< Vector of NodePtr
typedef Nodes::const_iterator NodesCIter; //!< Const iterator for Nodes
typedef Nodes::iterator NodesIter; //!< Iterator for Nodes

/** @cond INTERNAL */
namespace detail
{
class Commit;
typedef boost::shared_ptr< Commit > CommitPtr;
typedef boost::shared_ptr< const Commit > ConstCommitPtr;
}
/** @endcond */

}

#endif // DASH_DETAIL_TYPES_H
