
// Copyright (c) 2011 EPFL/BBP. All rights reserved.
// Author: Stefan Eilemann

#ifndef DASH_DASH_H
#define DASH_DASH_H

/**
 * @namespace dash
 * @brief Data Access and Sharing
 *
 * The dash library uses a per-thread Context to provide a view on the data. A
 * main context is made available by default, and can be used to create a new
 * context by copying it.
 *
 * The data is organized by Node and Attribute. Nodes form a directed acyclyc
 * graph and hold attributes. Attributes store any data.
 */

#include <dash/Context.h>
#include <dash/Node.h>
#include <dash/Vector.h>

#endif // DASH_DASH_H
