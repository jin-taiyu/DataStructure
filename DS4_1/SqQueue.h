#ifndef HEADER
#define HEADER

#include "public1.h"

typedef int QElemType;

#define MAXQSIZE 40 // 最大队列长度(对于循环队列，最大队列长度要减1)

// 此处给出循环队列的定义
typedef struct {
    QElemType * base;
    int front;
    int rear;
}SqQueue;


 //  循环队列的基本操作(9个)
 Status InitQueue(SqQueue &Q);


 Status DestroyQueue(SqQueue &Q);


 Status ClearQueue(SqQueue &Q);


 Status QueueEmpty(SqQueue Q);


 int QueueLength(SqQueue Q);


 Status GetHead(SqQueue Q,QElemType &e);


 Status EnQueue(SqQueue &Q,QElemType e);


 Status DeQueue(SqQueue &Q,QElemType &e);


 Status QueueTraverse(SqQueue Q,void(*vi)(QElemType));

void PrintElement(QElemType e);

#endif // header guard

