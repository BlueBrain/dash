
/* Copyright (c) 2011, EFPL/Blue Brain Project
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

#ifndef DASH_API_H
#define DASH_API_H

/**
 * @file dash/api.h
 *
 * Defines shared library symbol visibility macros.
 */

#if defined(_MSC_VER) || defined(__declspec)
#  define DASH_DLLEXPORT __declspec(dllexport)
#  define DASH_DLLIMPORT __declspec(dllimport)
#else // _MSC_VER
#  define DASH_DLLEXPORT
#  define DASH_DLLIMPORT
#endif // _MSC_VER

#if defined(DASH_STATIC)
#  define DASH_API
#elif defined(DASH_SHARED)
#  define DASH_API DASH_DLLEXPORT
#else
#  define DASH_API DASH_DLLIMPORT
#endif

#endif // DASH_API_H
