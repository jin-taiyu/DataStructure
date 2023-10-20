#ifndef LINKQUEUE_H_INCLUDED
#define LINKQUEUE_H_INCLUDED

#include "public1.h"
typedef int QElemType;

typedef struct QNode {
    QElemType data;
    struct QNode * next;
}QNode, * QueuePtr;

typedef struct {
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;

Status InitQueue(LinkQueue &Q);
Status DestroyQueue(LinkQueue &Q);
Status QueueEmpty(LinkQueue &Q);
Status EnQueue(LinkQueue &Q, QElemType e);
Status DeQueue(LinkQueue &Q, QElemType &e);

#endif // LINKQUEUE_H_INCLUDED
