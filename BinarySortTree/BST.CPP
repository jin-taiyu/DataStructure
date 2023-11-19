// 动态查找表(二叉排序树)的基本操作(8个)
#include"BiTree.h"
#include"public1.h"
#include"BST.h"


Status InitDSTable(BiTree &DT) {
    // 操作结果: 构造一个空的动态查找表DT
    DT=NULL;
    return OK;
}

void DestroyDSTable(BiTree &DT) {
    // 初始条件: 动态查找表DT存在。操作结果: 销毁动态查找表DT
    if(DT) {
        // 非空树
        if(DT->lchild) // 有左孩子
            DestroyDSTable(DT->lchild); // 销毁左孩子子树
        if(DT->rchild) // 有右孩子
            DestroyDSTable(DT->rchild); // 销毁右孩子子树
        free(DT); // 释放根结点
        DT=NULL; // 空指针赋0
    }
}

BiTree SearchBST(BiTree T,KeyType key) {
    // 在根指针T所指二叉排序树中递归地查找某关键字等于key的数据元素，
    // 若查找成功，则返回指向该数据元素结点的指针,否则返回空指针。算法9.5(a)
    if ((!T) || EQ(key, T->data.key)) return(T);
    else if (LT(key, T->data.key)) return(SearchBST(T->lchild, key));
    else return(SearchBST(T->rchild, key));
}

void SearchBST(BiTree &T,KeyType key,BiTree f,BiTree &p,Status &flag) {
    // 算法9.5(b)改
    // 在根指针T所指二叉排序树中递归地查找其关键字等于key的数据元素，若查找
    // 成功，则指针p指向该数据元素结点，并返回TRUE，否则指针p指向查找路径上
    // 访问的最后一个结点并返回FALSE,指针f指向T的双亲，其初始调用值为NULL
    if (!T) {p = f; flag = FALSE; return;}
    else if (EQ(key, T->data.key)) {p = T; flag = TRUE; return;}
    else if (LT(key, T->data.key)) {SearchBST(T->lchild, key, T, p, flag);}
    else {SearchBST(T->rchild, key, T, p, flag);}
}

Status InsertBST(BiTree &T, ElemType e) {
    // 当二叉排序树T中不存在关键字等于e.key的数据元素时，插入e并返回TRUE，
    // 否则返回FALSE。算法9.6(改)
    BiTree p = nullptr;
    Status flag = FALSE;
    SearchBST(T, e.key, nullptr, p, flag);
    if (!flag) {
        BiTree s = (BiTree) malloc(sizeof(BiTNode));
        s->data = e;
        s->lchild = s->rchild= nullptr;
        if (!p) T = s;
        else if (LT(e.key, p->data.key)) p->lchild = s;
        else p->rchild = s;
        return TRUE;
    }
    else return FALSE;
}

void Delete(BiTree &p) {
    // 从二叉排序树中删除结点p，并重接它的左或右子树。算法9.8
    BiTree q = nullptr;
    BiTree s = nullptr;
    if (!p->rchild) { //右子树空则只需要重接它的左子树
        q = p;
        p = p->lchild;
        free(q);
    }
    else if (!p->lchild) { //只需要重接它的右子树
        q = p;
        p = p->rchild;
        free(q);
    }
    else { //左右子树均不空
        q = p;
        s = p->lchild;
        while (s->rchild) {q = s; s = s->rchild;} //转左然后向右走到尽头
        p->data = s->data;
        if (q != p) q->rchild = s->lchild;
        else q->lchild = s->lchild;
        delete s;
    }
}

Status DeleteBST(BiTree &T,KeyType key) {
    // 若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素结点，
    // 并返回TRUE；否则返回FALSE。算法9.7
    if (!T) return FALSE;
    else {
        if (EQ(key, T->data.key)) Delete(T);
        else if (LT(key, T->data.key)) return DeleteBST(T->lchild, key);
        else return DeleteBST(T->rchild, key);
    }
    return OK;
}

void TraverseDSTable(BiTree DT,void(*Visit)(ElemType)) {
    // 初始条件: 动态查找表DT存在，Visit是对结点操作的应用函数
    // 操作结果: 按关键字的顺序对DT的每个结点调用函数Visit()一次且至多一次
    if(DT)
    {
        TraverseDSTable(DT->lchild,Visit); // 先中序遍历左子树
        Visit(DT->data); // 再访问根结点
        TraverseDSTable(DT->rchild,Visit); // 最后中序遍历右子树
    }
}

void RecursiveTraverse(BiTree DT, priority_queue<int, vector<int>, greater<int>> &minHeap) {
    if(DT) {
        RecursiveTraverse(DT->lchild, minHeap);
        minHeap.push(DT->data.others);
        RecursiveTraverse(DT->rchild, minHeap);
    }
}

int kthSmallest(BiTree DT, int kth, priority_queue<int, vector<int>, greater<int>> &minHeap) {
    // 递归访问把相关数据放入优先队列
    RecursiveTraverse(DT, minHeap);
    int tmp;
    int count = 0;
    while (!minHeap.empty()) {
        tmp = minHeap.top();
        minHeap.pop();
        count++;
        if (count == kth) {
            return tmp;
        }
    }
    return -1;
}
