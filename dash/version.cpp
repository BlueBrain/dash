
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

#include <dash/version.h>
#include <sstream>

namespace dash
{

int Version::getMajor() 
{
    return DASH_VERSION_MAJOR; 
}

int Version::getMinor()
{
    return DASH_VERSION_MINOR; 
}

int Version::getPatch() 
{
    return DASH_VERSION_PATCH; 
}

std::string Version::getString()
{
    std::ostringstream version;
    version << DASH_VERSION_MAJOR << '.' << DASH_VERSION_MINOR << '.' 
            << DASH_VERSION_PATCH;
    return version.str();
}

}
