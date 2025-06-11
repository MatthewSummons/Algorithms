# Heaps

The source code here implements various heaps.

## Standard Heap

The standard heap can be found in `heap.cpp` and has the implementation of building a max-heap using sift-up and sift-down operations, as well as a benchmarking script to test their performance. 
Building a max-heap using sift-down can be done in linear time in its **worst case** while building a max-heap using sift-up can be done in linear time in its **average case** with a **worst case** performance of log-linear time O(nlogn).

The benchmarks run on my machine demonstrate this, showing that constructions with sift-up and sift-down although both being linear in average case, have different constants.
The sift-down implementation is faster than the sift-up implementation.

<center>

| Size    | Avg Heapify Sift-Down (s) | Avg Heapify Sift-Up (s) |
| :------ | :-----------------------: | :-----------------------: |
| 10K     | 7.493473e-04              | 1.281791e-03              |
| 100K    | 7.559354e-03              | 1.287926e-02              |
| 500K    | 3.632142e-02              | 6.203074e-02              |
| 1M      | 7.332411e-02              | 1.300151e-01              |
| 2M      | 1.466754e-01              | 2.539173e-01              |

</center>