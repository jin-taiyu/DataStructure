#include "public1.h"
#include "BiTree.h"


typedef BiTree QElemType; 



// 单链队列－队列的链式存储结构。
typedef struct QNode{ 
	QElemType data;
	QNode *next;
}*QueuePtr;

struct LinkQueue{
	QueuePtr front,rear; // 队头、队尾指针
};



Status InitQueue(LinkQueue &Q);

Status DestroyQueue(LinkQueue &Q);

Status ClearQueue(LinkQueue &Q);

Status QueueEmpty(LinkQueue Q);

int QueueLength(LinkQueue Q);

Status GetHead(LinkQueue Q,QElemType &e);

Status QueueTraverse(LinkQueue Q,void(*visit)(QElemType));

Status  EnQueue(LinkQueue &Q,QElemType e);

Status DeQueue(LinkQueue &Q,QElemType &e);
