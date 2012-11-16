DASH                  {#mainpage}
====

## Description

DASH provides generic, efficient multi-threaded data access. It allows
data distribution and synchronization in heterogenous environments,
implemented by the CoDASH library. The primary use case is the
development of task-parallel multi-threaded applications.

DASH fulfils the following requirements:

* Memory efficient
    * All threads share the data and copy-on-write
    * Single-threaded use does not create any additional copies
    * Different data representations can share underlying data, e.g.,
      triangles between a BVH and kd-tree.
* High-Performance
    * Lock-free and wait-free read access
    * Change migration from thread A to B uses simple pointer swaps
* Distributable (see https://github.com/BlueBrain/codash)
    * Data update from node A to B shall only send change delta
    * Data discovery shall be transparent
* DAG structure
    * Access and distribution can handle a full graph
    * Selective distribution possible (partial data range, partial features)

## Downloads

* [Source Code](https://github.com/BlueBrain/dash/tags)
* [Ubuntu Packages Repository](https://launchpad.net/~eilemann/+archive/equalizer/)
