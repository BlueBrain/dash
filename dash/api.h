
// Copyright (c) 2011 EPFL/BBP. All rights reserved.
// Author: Stefan Eilemann

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
