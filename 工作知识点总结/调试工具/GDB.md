
摘自 《debugging with gdb the gnu source-level degugger》

# 第一章： 一个 GDB 会话样例

```shell
gdb m4
set width 100
break m4 changequote
run
n # next
s # step in subfunction
fin # finish to step out current subfunction
bt # backtrace
p lquote # print lquote
l # list 10 lines code
p len lquote=strlen(lquote)
c # continue
ctrl-d # quit
q # quit
```
print 命令不仅可以打印表达式的值，还可以调用子函数，也可以给表达式赋值

# 第二章：进入和离开 GDB
# 2.1 调用 GDB
```shell
gdb program
gdb program corefile
gdb program pid
# 带参数调试
# 也可以 gdb program
# 然后 set args arg1 arg2
gdb -args program arg1 arg2
```

### 2.1.1 选择文件
```shell
# 从 file 读入符号表
-symbols file
-s file

# 用文件 file 作为可执行文件来执行
-exec file
-e file

# 从 file 中读取符号表，并将 file 作为可执行程序
-se file

# 将 file 作为 coredump 文件
-core file
-c file

# 以 pid_number 为进程 id，作为 attach 的参数
-pid pid_number
-p pid_number

# 从 file 里执行 GDB 命令，参考 20.3
-command file
-x file

# 执行单一的 GDB 命令
-evaal-command command
-ex command
# 例如
gdb -ex 'set args 1 2' -ex 'run' program

# 将 dir 作为源码和脚本文件的搜索路径
-directory dir
-d dir

# 立即读入每一个符号文件的符号表，而不是默认的那种在需要的时候才渐次读入
-readnow
-r
```

### 2.1.2 选择模式
GDB 有多种运行模式：批处理模式、安静模式
```shell
# 不执行任何初始化文件里面的命令。通常在处理完所有命令选项和参数以后，才会执行这些文件里的命
-nx
-n

# 安静模式。不显示任何信息，只执行命令
-quiet
-silent
-q

# 以批处理模式运行。
-batch

-batch-silent

# 返回紫禁城的返回值
-return-child-result

# 无窗口，以 GUI 模式影响
-nw
-nwindows

# 以 dir 作为工作目录
-cd dir

# 每次栈显示的时候以标准且可识别的方式输出完整的文件名和行号
-fullname
-f

-epoch

# 设置 GDB 的注释级别，与 'set annotate level' 命令相同
# 通常是 1 级或 3 级
-annotate level

# 改变命令行的转义
-args

# 设置串口的运行速率
-baud bps
-b bps

# 设置 GDB 调用用处调试的链接超时时间（以秒为单位）
-timeout time

# 以 device 为标准输入输出
-tty device
-t device

# 启动时激活文本用户接口
-tui

-interpreter interp

# 以可读可写的方式打开可执行文件和 core 文件
-write

# 打印时间和内存使用统计信息
-statistics

# 打印 GDB 的版本信息
-version
```

### 2.1.3 GDB 在启动阶段的活动
- 启动命令行解释器
- 读入 home 目录下的初始化文件（如果有的话），然后执行里面的所有命令
- 处理命令行选项和参数
- 读入和执行在当前工作目录下的初始化文件（如果有的话）里的命令，只有当前目录和工作目录不通时才会执行
- 读入命令文件（用 -x 选项指定）里的命令（参考20.3）
- 读入记录在历史文件里的命令历史（参考19.3）

GDB 初始化文件通常称为 '.gdbinit'，位于用户的主目录下。

## 2.2 退出 GDB
```shell
quit
q
```

## 2.3 shell 命令
在调试期间，如果要执行 shell 命令，可以使用 shell 命令，而不用离开 GDB：
```
shell command string

# 如果是 make 命令，可以不带 shell 前缀
make make-args
```

## 2.4 日志输出
如果想把 GDB 命令的输出保存到一个文件里，可以用以下命令：
```shell
set logging on
set logging off
set logging file filename
# 默认以附加的方式保存，如果想以覆盖方式，则加上 overwrite 选项
set logging overwrite on
# 默认会打印日志到终端和logfile，如果只想输出到 logfile，则加上 
set logging redirect on
# 显示当前日志设置
show logging
```

# 第三章：GDB 命令
如果缩写无歧义，可以把 GDB 命令缩写为开头的几个字母（比如 'info' 命令前缀，可以写成 'i'）；  
也可以用回车来重复上一个命令；  
可以用 TAB 键来补全命令。

## 3.1 命令语法
ctrl-o 可以用来绑定复杂的需要重复的命令：该命令接受一个当前行，例如一个回车，接着从历史命令里取得相对于当前行的下一行来编辑。

## 3.2 命令补全
TAB 键可以帮忙补全命令

```shell
(gdb) info b<TAB>
(gdb) info breakpoints
```

## 3.3 帮助
help （缩写h）命令可以用来查看 GDB 的所有命令，也可以用 help 命令来查看某个命令的详细信息。

```shell
# complete args 可以列出所有可能的补全结果
complete args
(gdb) complete i
if
ignore
info
inspect

# 可以用 set 命令把一个表达式的值来设置一个环境变量
set prompt $ # 把提示符设置成 $
# show 和 info 不同，show 描述的是 GDB 内部的状态，而 info 描述的是程序的状态。你可以用 set 命令来改变大多数你可以用 show 显示的内容

```

# 第四章 在 GDB 里运行程序
## 4.1 为调试而编译
为了有效调试程序，需要在编译程序的时候产生调试信息。调试信息在目标文件里；调试信息描述了数据和函数的类型，源码和可执行程序的对应关系。
```shell
# 编译时候指定 '-g‘ 选项可以产生调试信息，推荐编译的时候总是带上。
# GCC,GNU CC/C++ 编译器下 -O 和 -g 是可以同时指定的。
```

## 4.2 运行程序
```shell
# start 命令可以用来在执行 main 函数开始前的一些静态变量的初始化
(gdb) start
# 开始运行程序
(gdb) run
```

## 4.3 运行参数
```shell
# set args 命令可以用来设置程序参数
set args arg1 arg2 ...

# 显示当前程序参数
show args
```

## 4.4 运行环境变量
```shell
# 显示可执行程序的搜索路径列表（PATH环境变量）
show path

# 显示可执行程序的环境变量
show environment
show env
show env varname
set env varname=value
unset env varname
```

## 4.5 工作目录
```shell
# 指定工作目录
(gdb) cd dir
# 显示当前工作目录
(gdb) pwd
```

## 4.6 程序的输入输出
```shell
# 使用 run 重定向程序的输入/输出
(gdb) run < file1 > file2

# 使用 tty 设置输入输出设备
tty /dev/ttyb
set inferior-tty /dev/ttyb

show inferior-tty
```

## 4.7 调试正在运行的程序
```shell
(gdb) attach pid

# 结束调试，让程序继续运行，和 quit 效果一样
# 如果是 run 运行的，则会 kill 这个进程
detatch
```

## 4.8 kill child proccess
```shell
(gdb) kill
```

## 4.9 调试多线程程序
```shell
# 切换线程
thread thread-number
# 显示所有线程
info threads
# 对线程列表执行命令，例如线程特定断点
thread [thread-number] [all] args
# 控制线程开始和结束的时候打印消息
set print thread-events on
set print thread-events off
show print thread-events
```

## 4.10 调试多进程程序
## 4.11 为跳转设置书签
```shell
# 保存被调试程序当前执行状态的快照
checkpoint

info checkpoints

restart checkpoint-id

delete checkpoint checkpoint-id
```

# 第五章 中断和继续
```shell
# 显示程序状态：是否在执行，什么进程，为什么中断
info program
```

## 5.1 断点，监视点，捕获点
- 断点：可以让程序在执行到某个点停止下来
- 监视点：监视点是特殊的断点，在表达式的值改变的时候中断程序
- 捕获点：捕获点是另一种特殊的断点，用来在某些事件发生的时候中断程序，例如在C++异常或者加载库的时候

### 5.1.1 设置断点
```shell
# 给指定的位置设置断点：可以是函数名，行号，或者一个指令的地址
(gdb) break location

# 不带参数的情况下，会在当前栈里的下一条指令里设置断点
# 这个在循环里面很好用
(gdb) break

# 带参数设置断点，在每次断点到达的时候计算 cond 表达式，并且当且仅当表达式的值不为零的时候中断
(gdb) break location if cond

# 设置一个只中断一次的断点，args 和 break 的含义一致
(gdb) tbreak args

# 设置一个硬件支持的断点
(gdb) hbreak args

# 设置一个硬件支持的且只中断一次的断点
(gdb) thbreak args

# 在所有匹配正则表达 regex 的函数上设置断点
# 在调试C++程序中很有用，在非特定类成员函数的重载函数设置断点，rbreak 很好用
(gdb) rbreak regex

# 也可以用 rbreak 在一个程序的所有函数上设置断点
(gdb) rbreak .

# 打印断点，监视点，捕获点表
# 可选参数 n 指定打印第几个断点，监视点，捕获点
info breakpoints [n]
info break [n]
info watchpoints
info catchpoints

# 还有很多跟共享库相关，跟解析断点地址相关的技巧就不再列举了，很少会用到

```

### 5.1.2 设置监视点
```shell

```