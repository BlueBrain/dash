
/* Copyright (c) 2011-2012, EPFL/Blue Brain Project
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

#ifndef DASH_API_H
#define DASH_API_H

#include <lunchbox/api.h>

/**
 * @file dash/api.h
 *
 * Defines shared library symbol visibility macros.
 */

#if defined(DASH_STATIC)
#  define DASH_API
#elif defined(DASH_SHARED)
#  define DASH_API LB_DLLEXPORT
#else
#  define DASH_API LB_DLLIMPORT
#endif

#endif // DASH_API_H
