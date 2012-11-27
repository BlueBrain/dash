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
    * Different data representations may share underlying data, e.g.,
      triangles between a BVH and kd-tree.
* High-Performance
    * Lock-free and wait-free read access
    * Fast write access after first copy-on-write
    * Change migration from thread A to B uses simple pointer swaps
* DAG structure
    * Access, context mapping and data distribution handles full graphs
    * Selective distribution shall be possible (partial data range,
      partial features)
* Distributable
    * See [codash](https://github.com/BlueBrain/codash)
    * Data update from node A to B shall only send change delta
    * Data discovery shall be transparent

## Downloads

* [Source Code](https://github.com/BlueBrain/dash/tags)
* [Ubuntu Packages Repository](https://launchpad.net/~eilemann/+archive/equalizer/)
* [Binary Packages](https://github.com/BlueBrain/dash/downloads)
* [API Documentation](http://bluebrain.github.com/)

## Support

Open an [issue](https://github.com/BlueBrain/dash/issues/new) if you
need help, have a question, want to provide feedback or need
advice. We'll try to resolve them in a timely manner.
