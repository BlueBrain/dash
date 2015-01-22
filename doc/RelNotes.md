Release Notes {#RelNotes}
============

[TOC]

# Introduction {#Introduction}

Welcome to DASH, a C++ library for generic, efficient multi-threaded Data
Access and Sharing. This is a bugfix release for the initial release of DASH,
which provides the following features:

* dash::Attribute providing generic data storage.
* dash::Node forming generic directed acyclic graphs and storing attributes
* dash::Context providing thread-safe access to attributes and nodes using
  copy-on-write data protection
* dash::Commit to migrate data modifications from context to context

# New in this release {#New}

## New Features {#NewFeatures}

* High-performance, minimally invasive illusion of distributed memory in
  parallel shared-memory applications.
* Simple and modern C++ API

## Enhancements {#Enhancements}

* Initial release, no enhancements

## Optimizations {#Optimizations}

* Initial release, no optimizations

## Documentation {#Documentation}

* [API documentation](http://bluebrain.github.io/dash-1.0/index.html)
  of the public DASH API

## Bug Fixes {#Fixes}

DASH 1.0.2 fixes the following bugs:

* [Fix racy unit tests](https://github.com/BlueBrain/dash/pull/18)

DASH 1.0.1 fixes the following bugs:

* Compilation and packaging issues on newer operating systems

## Known Bugs {#Bugs}

The following bugs were known at release time. Please file a
[Bug Report](https://github.com/BlueBrain/dash/issues) if you find
any other issue with this release.

* No known bugs

# About {#About}

DASH is a cross-platform library, designed to run on any modern operating
system, including all Unix variants and the Windows operating system. DASH uses
CMake to create a platform-specific build environment. The following platforms
and build environments are tested:

* Linux: Ubuntu 14.04 RHEL 6.5 (Makefile, i386, x64)
* Mac OS X: 10.9 (Makefile, XCode, i386, x64)

The
[API documentation](http://bluebrain.github.io/dash-1.0/index.html)
can be found on [bluebrain.github.io](http://bluebrain.github.io/). As
with any open source project, the available source code, in particular
the [unit tests](https://github.com/BlueBrain/dash/tree/1.0/tests)
provide a reference for developing applications.

# Errata
