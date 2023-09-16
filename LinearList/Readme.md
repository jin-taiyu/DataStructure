# 线性表操作程序

简单的线性表操作程序，实现了以下功能：

1. 初始化线性表
2. 在表头插入数据
3. 在表尾插入数据
4. 查询元素位置
5. 查询元素值
6. 删除元素
7. 销毁线性表
8. 删除线性表中所有带有固定值的数据元素

## 使用方法

### 初始化线性表

通过 `InitList` 函数初始化一个空的顺序表。示例代码：

```cpp
SqList L;
Status i = InitList(L);
```

### 在表头插入数据

使用 `ListInsert` 函数在顺序表的表头插入数据。示例代码：

```cpp
int j = 5; // 要插入的数据
Status result = ListInsert(L, 1, j); // 在表头插入数据
```

### 在表尾插入数据

示例代码：

```cpp
int j = 5; // 要插入的数据
L.elem[L.length] = j; // 在表尾插入数据
L.length++;
```

### 查询元素位置

使用 `LocateElem` 函数根据数据元素的值，在线性表中查找其位置。示例代码：

```cpp
int value = 1; // 要查找的元素值
int position = LocateElem(L, value, comp); // 查找元素的位置
```

### 查询元素值

使用 `GetElem` 函数根据位置查询元素的值。示例代码：

```cpp
int i = 5; // 要查询的位置
ElemType e;
Status result = GetElem(L, i, e); // 查询元素值
```

### 删除元素

使用 `ListDelete` 函数删除顺序表中的数据元素。示例代码：

```cpp
int i = 3; // 要删除的元素位置
ElemType e;
Status result = ListDelete(L, i, e); // 删除元素
```

### 销毁线性表

通过 `DestroyList` 函数销毁线性表。示例代码：

```cpp
Status result = DestroyList(L); // 销毁线性表
```

### 删除线性表中所有带有固定值的数据元素

示例代码：

```cpp
int x = 5; // 要删除的固定值
DeleteAllX(L, x); // 删除线性表中所有带有固定值的数据元素
```

## 示例测试程序

运行程序后，将进入一个简单的菜单界面，可以选择不同的操作，包括插入数据、删除数据、删除所有带有固定值的数据元素以及退出程序。
