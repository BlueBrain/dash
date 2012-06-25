
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

#ifndef DASH_VERSION_H_
#define DASH_VERSION_H_

#include <string>

namespace dash
{
    /** The current major version. */
#   define DASH_VERSION_MAJOR @VERSION_MAJOR@

    /** The current minor version. */
#   define DASH_VERSION_MINOR @VERSION_MINOR@

    /** The current patch level. */
#   define DASH_VERSION_PATCH @VERSION_PATCH@

    /** The Lunchbox version used for linking. */
#   define DASH_LUNCHBOX_VERSION @LUNCHBOX_VERSION@

/** True if the current version is newer than the given one. */
#   define DASH_VERSION_GT( MAJOR, MINOR, PATCH )                      \
    ( (DASH_VERSION_MAJOR>MAJOR) ||                                    \
      (DASH_VERSION_MAJOR==MAJOR && (DASH_VERSION_MINOR>MINOR ||      \
                     (DASH_VERSION_MINOR==MINOR && DASH_VERSION_PATCH>PATCH))))

/** True if the current version is equal or newer to the given. */
#   define DASH_VERSION_GE( MAJOR, MINOR, PATCH )                      \
    ( (DASH_VERSION_MAJOR>MAJOR) ||                                    \
      (DASH_VERSION_MAJOR==MAJOR && (DASH_VERSION_MINOR>MINOR ||      \
                    (DASH_VERSION_MINOR==MINOR && DASH_VERSION_PATCH>=PATCH))))

/** True if the current version is older than the given one. */
#   define DASH_VERSION_LT( MAJOR, MINOR, PATCH )                      \
    ( (DASH_VERSION_MAJOR<MAJOR) ||                                    \
      (DASH_VERSION_MAJOR==MAJOR && (DASH_VERSION_MINOR<MINOR ||      \
                     (DASH_VERSION_MINOR==MINOR && DASH_VERSION_PATCH<PATCH))))

/** True if the current version is older or equal to the given. */
#   define DASH_VERSION_LE( MAJOR, MINOR, PATCH )                      \
    ( (DASH_VERSION_MAJOR<MAJOR) ||                                    \
      (DASH_VERSION_MAJOR==MAJOR && (DASH_VERSION_MINOR<MINOR ||      \
                    (DASH_VERSION_MINOR==MINOR && DASH_VERSION_PATCH<=PATCH))))

    /** Information about the current dash version. */
    class Version
    {
    public:
        /** @return the current major version of dash. */
        static int getMajor();

        /** @return the current minor version of dash. */
        static int getMinor();

        /** @return the current patch level of dash. */
        static int getPatch();

        /** @return the current dash version (MM.mm.pp). */
        static std::string getString();
    };
}

#endif // DASH_VERSION_H_
