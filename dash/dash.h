
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

#include <dash/Attribute.h>
#include <dash/Commit.h>
#include <dash/Context.h>
#include <dash/Node.h>
#include <lunchbox/base.h>

#endif // DASH_DASH_H
