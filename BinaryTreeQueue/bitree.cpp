#include "BiTree.h"
#include "LinkQueue.h"

// 二叉链表的基本操作

BiTree CreateTree(TElemType A[],TElemType B[],int ha,int la,int hb,int lb) {
    //ha和la分别是先序遍历序列的第一个和最后一个结点下标， hb和lb分别是中序遍历序列的第一个和最后一个结点下标，
	//初始调用函数时，ha=hb=0,la=lb=n-1,n为二叉树数据元素的个数
    BiTree current = (BiTree) malloc(sizeof(BiTNode));
    current->data = A[ha];
    if (hb < 0 || lb < 0 || hb >= lb || ha > la) return nullptr;
    int new_left_hb;
    int new_left_lb;
    int new_right_hb;
    int new_right_lb;
    for (int i = hb; i <= lb; i++)  {
        if (B[i] == A[ha]) {
            new_left_hb = hb;
            new_left_lb = i - 1;
            new_right_hb = i + 1;
            new_right_lb = lb;
        }
    }
    current->lchild = CreateTree(A, B, ha + 1, la, new_left_hb, new_left_lb);
    current->rchild = CreateTree(A, B, ha + 1, la, new_right_hb, new_right_lb);
    return current;
}


void visit(TElemType e) {
	printf("%c",e);
}

Status LevelOrderTraverse(BiTree T,void(*Visit)(TElemType)) {
    // 初始条件：二叉树T存在，Visit是对结点操作的应用函数
	// 操作结果：层序递归遍历T(利用队列)，对每个结点调用函数Visit一次且仅一次
    LinkQueue Q;
    InitQueue(Q);
    EnQueue(Q, T);
    while (!QueueEmpty(Q)) {
        BiTree tmp;
        DeQueue(Q, tmp);
        if (tmp) {
            Visit(tmp->data);
            EnQueue(Q, tmp->lchild);
            EnQueue(Q, tmp->rchild);
        }
    }
    return OK;
}


Status PrintTree(BiTree bt,int nLayer)  {
    /* 按竖向树状打印的二叉树 */
    return OK;
}

Status IsCompleteTree(BiTree T) {
    //判断一棵二叉树是否是完全二叉树
    return OK;

}

Status DestroyBiTree(BiTree &T) {
    // 初始条件：二叉树T存在。操作结果：销毁二叉树T
    return OK;
}
