# 单链表操作程序说明

该程序实现了一些常见的单链表操作，包括初始化、销毁、创建、插入、删除、查找、遍历、合并等操作。以下是程序中各个函数的简要说明：

## 初始化和销毁

### `Status InitList(LinkList &L)`
初始化一个空的单链表 `L`，包括头结点。

### `Status DestroyList(LinkList &L)`
销毁整个单链表 `L`，释放内存。

## 创建单链表

### `void CreateList(LinkList &L, int n)`
逆位序输入 `n` 个元素的值，建立带表头结构的单链线性表 `L`。

### `void CreateList2(LinkList &L, int n)`
正位序输入 `n` 个元素的值，建立带表头结构的单链线性表 `L`。

## 单链表信息获取

### `int ListLength(LinkList L)`
返回单链表 `L` 中数据元素的个数。

### `Status GetElem(LinkList L, int i, ElemType &e)`
获取单链表 `L` 中第 `i` 个元素的值。

### `LinkList GetElemPtr(LinkList L, int i)`
获取单链表 `L` 中第 `i` 个元素的指针。

### `int LocateElem(LinkList L, ElemType e)`
返回单链表 `L` 中第一个值为 `e` 的数据元素的位序，如果不存在则返回 0。

## 遍历单链表

### `void print(ElemType c)`
输出元素值。

### `Status ListTraverse(LinkList L, void (*visit)(ElemType))`
按序输出单链表的各个元素值。

## 插入和删除操作

### `Status ListInsert(LinkList &L, int i, ElemType e)`
在单链表 `L` 中第 `i` 个位置之前插入元素 `e`。

### `Status ListDelete(LinkList &L, int i, ElemType &e)`
在单链表 `L` 中删除第 `i` 个元素，并由 `e` 返回其值。

## 合并操作

### `void MergeList(LinkList &La, LinkList &Lb, LinkList &Lc)`
合并两个有序的单链表 `La` 和 `Lb`，并将结果存储在 `Lc` 中。

### `void MergeList2(LinkList &La, LinkList &Lb, LinkList &Lc)`
合并两个有序的单链表 `La` 和 `Lb`，重复的元素只保留一次，并将结果存储在 `Lc` 中。

## 高级操作

### `Status Reverse(LinkList &L)`
就地逆转单链表 `L`。

### `Status ReverseAsGroup(LinkList &L, int k)`
将单链表 `L` 每 `k` 个节点一组进行翻转。