 // 动态查找表中数据元素的定义和二叉树的二叉链表存储表示
#ifndef _BiTree_H
#define _BiTree_H

#define N 10 // 数据元素个数
typedef int KeyType; // 设关键字域为整型
typedef struct ElemType // 数据元素类型
 {
   KeyType key;
   int others;
 }ElemType,TElemType;

typedef struct BiTNode
 {
   TElemType data;
   BiTNode *lchild,*rchild; // 左右孩子指针
 }BiTNode,*BiTree;

#endif