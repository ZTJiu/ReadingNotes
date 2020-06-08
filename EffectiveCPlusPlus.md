# 第一章 让自己习惯C++ 
## Item01 视C++为一个语言联邦
C++是一个多重泛型编程语言，同时支持：过程形式、面向对象形式、函数形式、泛型形式和元编程形式。

## Item02 尽量以const,enum,inline替换define
宁可以编译器替代预处理器。  
const常量在编译出错时候提示的是变量名，而define宏在预编译的时候直接替换的，在编译阶段出错只会提示替换后的符号，难以定位问题所在。  
define宏函数可维护性和可读性都比差，其省去函数调用开销的目的，可以用inline函数达到。

总之：  
对于单纯的常量，最好以const对象或enum替换define；  
对于形似函数的宏，最好以inline函数替换define；  

## Item03 尽可能使用const
1. const 出现在星号前面，表示被指物是常量；出现在星号后边，表示指针自身是常量；  
2. const 修饰迭代器，表示迭代器是不可变的（不能指向别的对象了），但是所指向的对象是可以改变的；  

## Item04 确定对象被使用前已被初始化
1. C++ 规定类成员变量的初始化动作发生在进入构造函数体之前（构造函数内部只能称作赋值操作，而不是初始化）。初始化通常效率更高。  
2. 基于赋值的做法，首先调用 default 构造函数为成员变量赋初值，然后再在构造函数内部做赋值操作。  
3. 基类早于子类被初始化，类内部成员变量的初始化顺序与其声明的顺序相同。  
4. staitc 对象的生命周期从构造完开始，直到 main() 函数调用结束。  

注： C++11 下，有三种 thread-safe 的数据初始化形式： 
1. 常量表达式； 
2. 使用 std::once_flag 调用 std::call_once 函数； 
3. 代码块儿内部的 static 变量；  
reference: https://www.modernescpp.com/index.php/thread-safe-initialization-of-data

# 第二章 构造/析构/赋值运算
## Item05 C++ 的默认生成函数
1. 编译器会自动为一个没声明构造函数、析构函数和赋值操作符的类自动生成： default构造函数、析构函数、拷贝构造函数和赋值操作符。

## Item06 若不想使用编译器自动生成的函数，就明确拒绝  
要拒绝某个自动生成的函数，传统做法是把这些函数声明为 private，并且不定义。  
在 C++11 中，可以直接使用 delete 关键字来拒绝。  

## Item07 为多态基类声明 virtual 析构函数
为多态基类声明 virtual 析构函数，否则在使用基类指针释放资源的时候，会导致派生类的资源没法正确释放（其析构函数不会被调用）。  
设计的不是用于继承基类的类，不要声明 virtual 析构函数，否则会导致编译器为这个类生成不必要的虚表。  

## Item08 别让异常逃离析构函数
1. 析构函数不要吐出异常，析构函数应该捕获所调用的其他函数里面抛出的异常；  
2. 

## Item09 绝不在构造和析构过程中调用 virtual 函数
在构造函数和析构函数里面不要调用 virtual 函数，因为这类调用不会下降到子类。

## Item10 让 operator= 返回一个 reference to *this
否则无法实现连锁赋值。  

## Item11 在 operator= 中处理自我赋值

## Item12 复制对象时勿忘其每一个成员

## Item13 以对象管理资源
1. 获得资源后立即放入管理对象  
2. 管理对象运用析构函数确保资源被正确释放  

## Item14 在资源管理类中小心copying行为 
1. 复制 RAII 对象必须一并复制它所管理的资源，资源的 copying 行为决定了 RAII 对象的 copying 行为  
2. 普遍而常见的 RAII 类 copying 行为：抑制 copying 行为，实施引用计数法  

## Item15 在资源管理类中提供访问原始资源的接口

## Item16 成对使用 new 和 delete 时要采用相同的形式
如果 new 的时候使用了 []，则 delete 的时候也必须使用 []  

## Item17 以独立的语句将 new 的对象放入智能指针

# 第四章
## Item18 让接口容易被正确使用，不易被误用

## Item19 设计 class 犹如设计 type

## Item20 以 pyss-by-reference-to-const 替换 pass-by-value

## Item21 必须放回对象时，别返回其 reference
绝不要返回一个指向 local stack 对象的 pointer 或 reference，也不要返回一个指向 heap-allocated 对象的 reference。

## Item22 将成员变量声明为 private

## Item23 
