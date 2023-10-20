#include "SqQueue.h"

//  循环队列的基本操作(9个)
Status InitQueue(SqQueue &Q) {
    // 构造一个空队列Q
    Q.base = (QElemType *) malloc(MAXQSIZE * sizeof(QElemType));
    if (!Q.base) {return OVERFLOW;}
    Q.front = Q.rear = 0;
    return OK;
}

Status DestroyQueue(SqQueue &Q) {
    // 销毁队列Q,Q不再存在
    //检查
    if (!Q.base) {return OK;}
    // 首先释放队列的数组部分,并置空
    free(Q.base);
    Q.base = nullptr;
    Q.front = Q.rear = 0;
    return OK;
}

Status ClearQueue(SqQueue &Q) {
    // 将Q清为空队列
    QElemType temp;
    while (!QueueEmpty(Q)) {
        if (DeQueue(Q, temp) != OK) {
            return ERROR; // 如果 DeQueue 操作失败，返回 ERROR
        }
    }
    if (QueueEmpty(Q)) {return OK;}
    return ERROR;
}

Status QueueEmpty(SqQueue Q) {
    // 若队列Q为空队列,则返回TRUE,否则返回FALSE
    if (!Q.base) {return TRUE;}
    if (Q.front == Q.rear) {return TRUE;}
    return FALSE;
}

int QueueLength(SqQueue Q) {
    // 返回Q的元素个数,即队列的长度
    if (Q.base == nullptr) {return 0;}
    return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

Status GetHead(SqQueue Q,QElemType &e) {
    // 若队列不空,则用e返回Q的队头元素,并返回OK,否则返回ERROR
    if (QueueEmpty(Q)) {return ERROR;}
    e = Q.base[Q.front];
    return OK;
}

Status EnQueue(SqQueue &Q,QElemType e) {
    // 插入元素e为Q的新的队尾元素
    // 队列满
    if ((Q.rear + 1) % MAXQSIZE == Q.front) {return ERROR;}
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAXQSIZE;
    return OK;
}

Status DeQueue(SqQueue &Q,QElemType &e) {
    // 若队列不空,则删除Q的队头元素,用e返回其值,并返回OK;否则返回ERROR
    if (QueueEmpty(Q)) {return ERROR;}
    e = Q.base[Q.front];
    Q.front = (Q.front + 1) % MAXQSIZE;
    return OK;
}

Status QueueTraverse(SqQueue Q,void(*vi)(QElemType)) {
    // 从队头到队尾依次对队列Q中每个元素调用函数vi().一旦vi失败,则操作失败
    for (int  i = Q.front; i < Q.rear; i++) {
        vi(Q.base[i]);
    }
    return OK;
}

void PrintElement(QElemType e) {
    cout << e << '  ';
}
