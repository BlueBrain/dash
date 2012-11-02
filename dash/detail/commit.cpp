
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

#include "commit.h"

#include "attribute.h"
#include "contextCommit.h"
#include "commitChange.h"
#include "contextChange.h"
#include "node.h"

#include <dash/context.h>
#include <dash/node.h>

namespace dash
{
namespace detail
{

Commit::Commit()
     : changes_()
     , context_()
{
}

Commit::~Commit()
{
}

Commit& Commit::operator = ( const ContextCommit& rhs )
{
    LBASSERT( changes_.empty( ));
    context_ = rhs.context_;
    CommitChanges::ScopedWrite mutex( changes_.getWriteLock( ));
    for( ContextChanges::const_iterator it = rhs.contextChanges_.begin();
         it != rhs.contextChanges_.end(); ++it )
    {
        changes_.push_back_unlocked( *it );
    }
    return *this;
}

bool Commit::operator == ( const Commit& rhs ) const
{
    if( this == &rhs )
        return true;

    if( changes_.size() != rhs.changes_.size( ))
        return false;

    ChangesCIter it = changes_.begin();
    ChangesCIter rhsIt = rhs.changes_.begin();
    for( ; it != changes_.end() && rhsIt != rhs.changes_.end();
         ++it, ++rhsIt )
    {
        if( *it != *rhsIt )
            return false;
    }

    return true;
}

void Commit::apply() const
{
    for( ChangesIter i = changes_.begin(); i != changes_.end(); ++i )
    {
        CommitChange& change = *i;
        switch( change.type )
        {
          case Change::NODE_INSERT:
              if( change.node->isMapped( ))
              {
                  context_->map( change.child, dash::Context::getCurrent( ));
                  change.node->insert( change.child );
              }
              else
                  LBINFO << "Ignoring Node::insert change, parent not mapped"
                         << std::endl;
              break;
          case Change::NODE_ERASE:
              if( !change.node->isMapped( ))
                  break;
              change.node->erase( change.child );
              break;

          case Change::ATTRIBUTE_INSERT:
              if( change.node->isMapped( ))
              {
                  context_->map( change.attribute,
                                 dash::Context::getCurrent( ));
                  change.node->insert( change.attribute );
              }
              else
                  LBINFO << "Ignoring Node::insert change, parent not mapped"
                         << std::endl;
              break;

          case Change::ATTRIBUTE_ERASE:
              if( !change.node->isMapped( ))
                  break;
              change.node->erase( change.attribute );
              break;

          case Change::ATTRIBUTE_CHANGED:
              change.attribute->getImpl()->apply( change );
              break;

          default:
              LBINFO << change << std::endl;
              LBUNIMPLEMENTED;
        }
    }
}

}
}
