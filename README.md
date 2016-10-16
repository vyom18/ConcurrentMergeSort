# ConcurrentMergeSort

This is the implementation of concurrent merge sort using fork() C system call.
<br>
Theoritically, the complexity should be O(n) (for n processor cores)
<br>
However, practically, there is a lot of process creation overhead, and hence, it runs even slower than the normal merge sort.
<br>
Maybe, by creating threads instead of processes, it will run faster? No idea! Will try and find out!
