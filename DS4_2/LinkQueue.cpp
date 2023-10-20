#include "LinkQueue.h"

Status InitQueue(LinkQueue &Q) {
    // 构造一个空队列Q
    Q.front = Q.rear = (QueuePtr ) malloc(sizeof(QNode));
    if (!Q.front) {return OVERFLOW;}
    Q.front->next = nullptr;
    return OK;
}

Status DestroyQueue(LinkQueue &Q) {
    // 销毁队列Q
    while (Q.front) {
        Q.rear = Q.front->next;
        free(Q.front);
        Q.front = Q.front->next;
    }
    return OK;
}

Status QueueEmpty(LinkQueue &Q) {
    if (Q.rear == Q.front) {return TRUE;}
    return FALSE;
}

Status EnQueue(LinkQueue &Q, QElemType e) {
    // 入队
    QueuePtr newnode = (QueuePtr) malloc(sizeof(QNode));
    if (!newnode) {return OVERFLOW;}
    newnode->next = nullptr;
    newnode->data = e;
    Q.rear->next = newnode;
    Q.rear = newnode;
    return OK;
}

Status DeQueue(LinkQueue &Q, QElemType &e) {
    if (Q.rear == Q.front) {return ERROR;} // 队空
    QueuePtr temp = Q.front->next;
    e = temp->data;
    Q.front->next = temp->next;
    if (Q.rear == temp) {Q.rear = Q.front;} // 删除最后一个元素后,列尾指针丢失了
    free(temp);
    return OK;
}
