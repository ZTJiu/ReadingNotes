# 第一章 类型推导
## 条款1： 理解模板类型推导

```c++
template<typename T>
void f(ParamType param);

f(expr); // 从 expr 推导 T 和 ParamType 的类型
```
分三种情况：

### 1. ParamType 是个指针或引用，但不是万能引用
1. 若 expr 具有引用类型，先将引用部分忽略；
2. 然后，对 expr 的类型和 ParamType 的类型执行模式匹配，来决定 T 的类型；

```c++
template<typename T>
void f(T& param); // param 是一个引用
```


# 第四章 智能指针
## 条款18：使用 std::unique_ptr 管理具备专属所有权的资源


## 条款19：使用 std::shared_ptr 管理共享所有权的资源