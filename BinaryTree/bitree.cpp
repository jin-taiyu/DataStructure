#include "BiTree.h"
// 二叉链表的基本操作

Status CreateBiTree(BiTree &T) {
    // 按完全先序序列输入二叉树中结点的值
    char ch;
    scanf("%c", &ch);
    if (ch == ' ') T = nullptr;
    else {
        if (!(T = (BiTNode *) malloc(sizeof(BiTNode)))) return (OVERFLOW);
        T->data = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
    return OK;
}

void visit(TElemType e) {
	printf("%c",e);
}

Status PreOrderTraverse(BiTree T,void(*Visit)(TElemType)) {
    // 初始条件：二叉树T存在，Visit是对结点操作的应用函数。
	// 操作结果：先序递归遍历T，对每个结点调用函数Visit一次且仅一次
	if (T != nullptr) {
        Visit(T->data);
        // 在这里我们的Visit函数并没有定义返回值
        // 导致事实上我们并没有办法检查是否成功访问
        // 因此我们也就不必为孩子的PreOrderTraverse设置检查
        // 甚至还提高了可读性
        PreOrderTraverse(T->lchild, Visit);
        PreOrderTraverse(T->rchild, Visit);
	}
    return OK;
}

Status InOrderTraverse(BiTree T,void(*Visit)(TElemType)) {
    // 初始条件：二叉树T存在，Visit是对结点操作的应用函数
	// 操作结果：中序递归遍历T，对每个结点调用函数Visit一次且仅一次
	if (T != nullptr) {
        InOrderTraverse(T->lchild, Visit);
        Visit(T->data);
        InOrderTraverse(T->rchild, Visit);
	}
    return OK;
}

Status PostOrderTraverse(BiTree T,void(*Visit)(TElemType)) {
    // 初始条件：二叉树T存在，Visit是对结点操作的应用函数
	// 操作结果：后序递归遍历T，对每个结点调用函数Visit一次且仅一次
	if (T != nullptr) {
        PostOrderTraverse(T->lchild, Visit);
        PostOrderTraverse(T->rchild, Visit);
        Visit(T->data);
	}
    return OK;
}

void CountLeaf (BiTree T,int &count) {
    //统计二叉树的叶子结点数
    if (T == nullptr) return;
    else {
        if (T->lchild == nullptr && T->rchild == nullptr)
            count++;
        else {
            CountLeaf(T->lchild, count);
            CountLeaf(T->rchild, count);
        }
    }
}

int TreeDepth (BiTree T){
    // 返回二叉树的深度
   if (T == nullptr) return 0;
   else {
        int depthLeft = TreeDepth(T->lchild);
        int depthRight = TreeDepth(T->rchild);
        return std::max(depthLeft, depthRight) + 1;
   }
}


Status PrintTree(BiTree bt,int nLayer) {
    /* 按竖向树状打印的二叉树 */
    if (bt != nullptr) {
        PrintTree(bt->lchild, nLayer + 1);
        for (int i = 1; i < nLayer; i++) {
            cout << "-";
        }
        cout << bt->data << endl;
        PrintTree(bt->rchild, nLayer + 1);
    }
    return OK;
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
