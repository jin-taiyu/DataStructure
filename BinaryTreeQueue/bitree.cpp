#include "BiTree.h"
#include "LinkQueue.h"

// 二叉链表的基本操作

BiTree CreateTree(TElemType A[],TElemType B[],int ha,int la,int hb,int lb) {
    //ha和la分别是先序遍历序列的第一个和最后一个结点下标， hb和lb分别是中序遍历序列的第一个和最后一个结点下标，
	//初始调用函数时，ha=hb=0,la=lb=n-1,n为二叉树数据元素的个数
    if (ha > la || hb > lb) return NULL;  // 递归终止条件

    // 创建根节点
    BiTNode* root = (BiTNode*)malloc(sizeof(BiTNode));
    if (root == nullptr) exit(OVERFLOW);
    root->data = A[ha];

    // 在中序遍历数组中找到根节点的位置
    int rootIndex = hb;
    while (rootIndex <= lb && B[rootIndex] != A[ha]) rootIndex++;

    ////////////////////////////////////////////////////////
    //           增加一点健壮性            //
    //////////////////////////////////////////////////////
    if (rootIndex > lb) {
        free(root);
    return NULL;  // 或其他错误处理
    }

    // 计算左子树和右子树的节点数量
    int leftLength = rootIndex - hb;
    int rightLength = lb - rootIndex;

    // 递归构建左子树和右子树
    root->lchild = CreateTree(A, B, ha + 1, ha + leftLength, hb, rootIndex - 1);
    root->rchild = CreateTree(A, B, ha + leftLength + 1, la, rootIndex + 1, lb);

    return root;
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
    DestroyQueue(Q); // 差点忘了释放空间
    return OK;
}


Status PrintTree(BiTree bt,int nLayer)  {
    /* 按竖向树状打印的二叉树 */
    if (bt != nullptr) {
        PrintTree(bt->lchild, nLayer + 1);
        for (int i = 0; i < nLayer; i++) {
            cout << " -";
        }
        cout << bt->data << endl;
        PrintTree(bt->rchild, nLayer + 1);
    }
    return OK;
}

Status IsCompleteTree(BiTree T) {
    //判断一棵二叉树是否是完全二叉树
    int flag = 0;
    LinkQueue Q;
    InitQueue(Q);
    EnQueue(Q,  T);
    while (!QueueEmpty(Q)) {
        BiTree tmp;
        DeQueue(Q, tmp);
        if (flag == 1 && tmp != nullptr) {
            DestroyQueue(Q);
            return FALSE;
        }
        if (tmp == nullptr) {
            flag = 1;
        }
        else {
            EnQueue(Q, tmp->lchild);
            EnQueue(Q, tmp->rchild);
        }
    }
    DestroyQueue(Q);
    return TRUE;
}

Status DestroyBiTree(BiTree &T) {
    // 初始条件：二叉树T存在。操作结果：销毁二叉树T
    if (T == nullptr) return OK;
    else {
        DestroyBiTree(T->lchild);
        DestroyBiTree(T->rchild);
        // 释放并置空
        free(T);
        T = nullptr;
    }
    return OK;
}

Status FindParent(BiTree &T, TElemType x, TElemType &parent) {
    LinkQueue Q;
    InitQueue(Q);
    EnQueue(Q, T);
    while (!QueueEmpty(Q)) {
        BiTree tmp;
        DeQueue(Q, tmp);
        if (tmp) {
            EnQueue(Q, tmp->lchild);
            EnQueue(Q, tmp->rchild);
            // 利用短路原则先判断左右子节点是否为空
            if (tmp->lchild != nullptr && tmp->lchild->data == x) {
                parent = tmp->data;
                // 在所有函数出口布置队列销毁
                DestroyQueue(Q);
                return OK;
            }
            if (tmp->rchild != nullptr && tmp->rchild->data == x) {
                parent = tmp->data;
                DestroyQueue(Q);
                return OK;
            }
        }
    }
    DestroyQueue(Q);
    return ERROR;
}

// 代码复用 用上次实验的代码
void FindParentNode(BiTree T, map<TElemType, TElemType> &parents) {
    if (T == nullptr) return;
    // 如果左孩子存在
    if (T->lchild) {
        parents[T->lchild->data] = T->data;
        // 继续找
        FindParentNode(T->lchild, parents);
    }
    if (T->rchild) {
        parents[T->rchild->data] = T->data;
        FindParentNode(T->rchild, parents);
    }
}

Status FindNearAncestors(BiTree T, map<TElemType, TElemType> &parents, TElemType &nodeFirst, TElemType &nodeSecond, TElemType &nearAncestor) {
    // 借助找父节点的函数
    // 打表
    FindParentNode(T, parents);
    vector<TElemType> prevFirst;
    vector<TElemType> prevSecond;
    // 把自己放进去
    prevFirst.push_back(nodeFirst);
    prevSecond.push_back(nodeSecond);

    TElemType first = nodeFirst;
    TElemType second = nodeSecond;
    while (parents[first]) {
        prevFirst.push_back(parents[first]);
        first = parents[first];
    }
    while (parents[second]) {
        prevSecond.push_back(parents[second]);
        second = parents[second];
    }
    // 开始逐个比较
    for (vector<TElemType>::iterator i = prevFirst.begin(); i < prevFirst.end(); i++) {
        for (vector<TElemType>::iterator j = prevSecond.begin(); j < prevSecond.end(); j++) {
            if (*i == *j) {
                nearAncestor = *i;
                return OK;
            }
        }
    }
    return ERROR;
}
