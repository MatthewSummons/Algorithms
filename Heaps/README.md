# Heaps

The source code here implements various heaps.

## Standard Heap

The standard heap can be found in `heap.cpp` and has the implementation of building a max-heap using sift-up and sift-down operations, as well as a benchmarking script to test their performance. 
Building a max-heap using sift-down can be done in linear time in its **worst case** while building a max-heap using sift-up can be done in linear time in its **average case** with a **worst case** performance of log-linear time O(nlogn).

The benchmarks run on my machine demonstrate this, showing that constructions with sift-up and sift-down although both being linear in average case, have different constants.
The sift-down implementation is faster than the sift-up implementation.

</center>

| Size      | Avg Heapify Sift-Down (s) | Avg Heapify Sift-Up (s)    | Speedup |
| :-------- | :------------------------: | :-----------------------: | :-----: |
| 10K       | 7.935101e-04               | 1.297801e-03              | x 1.64  |
| 100K      | 7.089416e-03               | 1.216276e-02              | x 1.72  |
| 500K      | 3.569100e-02               | 6.073563e-02              | x 1.70  |
| 1M        | 7.122314e-02               | 1.208400e-01              | x 1.70  |
| 2M        | 1.697562e-01               | 2.585091e-01              | x 1.52  |
| 10M       | 7.516278e-01               | 1.229631e+00              | x 1.64  |

</center>