# ConcurrentMergeSort

This is the implementation of concurrent merge sort using fork() C system call.So basically fork() is used to create a new process.It is system call by the OS only.
<br>
Theoritically, the complexity should be O(n) (for n processor cores)
<br>
However, practically, there is a lot of process creation overhead, and hence, it runs even slower than the normal merge sort.
<br>
Maybe, by creating threads instead of processes, it will run faster? No idea! Will try and find out!
But generaly we can say that the thread are faster than the processes.But due to some overhead It can take more time than simple merge sort.So Let's Find Out By running program!!!
