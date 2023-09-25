#ifndef HEADER
#define HEADER

 typedef int ElemType;
//单链表的存储定义
typedef struct LNode
{
    ElemType         data;
    struct LNode   *next;
}LNode, *LinkList;

#endif // header guard

