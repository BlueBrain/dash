
// Copyright (c) 2011 EPFL/BBP. All rights reserved.
// Author: Stefan Eilemann

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
