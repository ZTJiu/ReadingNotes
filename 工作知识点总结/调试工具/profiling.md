在软件工程中 profiling（program profiling or software profiling，参考 [wikipedia](https://en.wikipedia.org/wiki/Profiling_(computer_programming))）含义如下：
profiling 是一种动态分析程序内存占用和时间占用的方法。
# profiling tools
profiling tools 用来分析代码的执行效率，找出代码中消耗时间最多的部分。
profiling tools 分为两类：
- 运行时分析工具：运行时分析工具会分析代码的执行过程，找出代码中消耗时间最多的部分。
- 编译时分析工具：编译时分析工具会分析代码的执行过程，找出代码中消耗时间最多的部分。

# 常用工具

https://euccas.github.io/blog/20170827/cpu-profiling-tools-on-linux.html

https://www.brendangregg.com/perf.html

https://perf.wiki.kernel.org/index.php/Tutorial



- time 命令：会显示代码执行的时间： real = user + sys，user = 用户态代码执行时间，sys = 内核态代码执行时间。根据这两个时间，可以判断代你的程序是 CPU-bound 还是 I/O-bound。
- 
