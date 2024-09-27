在计算机领域，page fault（页错误）是指当程序试图访问的页面，但该页面可能不存在或不可访问时，由内存管理单元引发的一种异常。

# 类型
## minor
在发生Page fault时，如果该页已经被加载到内存中了，但是还没被MMU标记，我们称这样的Page fault为minor或者soft page fault。这样的Page fault不会导致进程被阻塞，因为该页已经被加载到内存中了。

通常发生在共享内存的过程中，一个进程已经把页加载到内存中了，另一个进程发生page fault时，该页已经在内存中了，不需要从磁盘读取。

## major
如果发生Page fault时，该页还没有被加载到内存中，那么我们称这样的Page fault为major或者hard page fault。操作系统为了增加进程的可用内存量，通常会延迟分配内存，或延迟加载磁盘数据到内存。

## Invalid
如果进程试图访问不属于虚拟地址空间的地址，则会除非 invalid page fault。比如访问了NULL指针。操作系统会把发生这种类型page fault的进程杀掉。

# Invalid conditions
访问非法地址或者发生invalid page fault，都会导致segmentation fault或bus error。

# Performance impact
Page faults degrade system performance and can cause thrashing. Major page faults on conventional computers using hard disk drives can have a significant impact on their performance, as an average hard disk drive has an average rotational latency of 3 ms, a seek time of 5 ms, and a transfer time of 0.05 ms/page. Therefore, the total time for paging is near 8 ms (= 8,000 μs). If the memory access time is 0.2 μs, then the page fault would make the operation about 40,000 times slower.

Performance optimization of programs or operating systems often involves reducing the number of page faults. Two primary focuses of the optimization are reducing overall memory usage and improving memory locality. To reduce the page faults, developers must use an appropriate page replacement algorithm that maximizes the page hits. Many have been proposed, such as implementing heuristic algorithms to reduce the incidence of page faults.

A larger physical memory also reduces page faults.
