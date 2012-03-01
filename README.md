# DASH

## Description

The goal of DASH is to address generic, efficient multi-threaded data
access, data distribution and synchronization in heterogenous environments.
The primary use case is the development of task-parallel multi-core,
distributed applications. The implementation of data parallel operations
is possible, but not facilitated by dash.

DASH fulfils the following requirements:

* Memory efficient
    * All threads share the data and copy-on-write
    * Single-threaded use shall not create any additional copies
    * Different data representations can share underlying data, e.g., triangles between BVH and kd-tree.
* High-Performance
    * Lock-free read access
    * Data update from thread A to B shall be a simple pointer swaps
* Distributable (Not yet implemented)
    * Data update from node A to B shall only send change delta
    * Data discovery shall be transparent
* DAG structure
    * Access and distribution can handle a full graph
    * Selective distribution possible (partial data range, partial features)
