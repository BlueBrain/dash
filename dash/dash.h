
/* Copyright (c) 2011-2012, EFPL/Blue Brain Project
 *                          Stefan.Eilemann@epfl.ch
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
 * The dash library uses a per-thread Context to provide an isolated view on the
 * data stored in Node and Attribute. Nodes form a directed acyclyc graph and
 * hold attributes. Attributes store any data. Modifications are migrated
 * between contexts using a Commit.
 */

#include <dash/attribute.h>
#include <dash/commit.h>
#include <dash/context.h>
#include <dash/node.h>
#include <lunchbox/lunchbox.h>

#endif // DASH_DASH_H
