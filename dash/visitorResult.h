
/* Copyright (c) 2011, EPFL/Blue Brain Project
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

#ifndef DASH_VISITORRESULT_H
#define DASH_VISITORRESULT_H

#include <iostream>

namespace dash
{
/** The result code from any accept() operation. @version 0.1 */
enum VisitorResult
{
    ACCEPT_CONTINUE,   //!< continue the traversal
    ACCEPT_TERMINATE,  //!< abort the traversal
    ACCEPT_PRUNE       //!< do not traverse current entity downwards
};

/** Output the visitor result in human-readable form. @version 0.1 */
inline std::ostream& operator << ( std::ostream& os, const VisitorResult& r )
{
    switch( r )
    {
      case ACCEPT_CONTINUE: return os << "continue";
      case ACCEPT_TERMINATE: return os << "terminate";
      case ACCEPT_PRUNE: return os << "prune";
      default: return os << "ERROR";
    }
}

}
#endif // DASH_VISITORRESULT_H
