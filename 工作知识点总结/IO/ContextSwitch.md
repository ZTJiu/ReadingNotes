[Context Switch wiki](https://en.wikipedia.org/wiki/Context_switch)

概念：context switch 在计算机领域是指线程或者进程存储状态的过程。为了在单核CPU上同时运行多个进程或者线程，CPU从当前进程或者线程切换到另一个进程或者线程的过程中，保留前一个的状态，以便在切换回来的时候从上次的状态继续运行。

# 代价
context switch 是计算密集型的操作，涉及到保存寄存器，内存map

context switch 过程：
