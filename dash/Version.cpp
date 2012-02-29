
// Copyright (c) 2011 EPFL/BBP. All rights reserved.
// Author: Stefan Eilemann

#include <dash/Version.h>
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
