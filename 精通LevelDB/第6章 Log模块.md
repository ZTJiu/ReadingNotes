介绍预写日志 Wrte-Ahead Log

# 6.1 Log文件格式定义
Log文件格式定义如下：
```text
crc(4) | len(2) | type(1) | content
```
type 共有 4 种：
```cpp
kFullType = 1,
kFirstType = 2,
kMiddleType = 3,
kLastType = 4
```
kFullType 表示一条记录完整地写到了一个块上。当一条记录跨几个块时，kFirstType 表示该记录的第一部分，kMiddleType 表示该记录的中间部分，kLastType 表示该记录的最后一部分。

```text
一个块中包含多条记录：
block: header | record1 | header | record2 | ... | header | recordN | trailer

一条记录跨多个块：
block1: header | record | trailer
block2: header | record | trailer
block3: header | record | trailer
```

# 6.2 Log文件读写操作
# 6.2.1 Log文件写入
```cpp
// db/log_writer.h and db/log_writer.cc
Status AddRecord(const Slice& slice);
```