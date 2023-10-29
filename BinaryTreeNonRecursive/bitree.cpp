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
    stack<BiTree> s;
    s.push(T);
    while (!s.empty()) {
        BiTree p;
        while (p = s.top()) s.push(p->lchild); // 向左走到尽头
        s.pop();
        if (!s.empty()) {
            p = s.top();
            s.pop();
            Visit(p->data);
            s.push(p->rchild);
        }
    }
    return OK;
    /*
    或者采用TAOCP中给出的非递归中序遍历算法：

    算法 T（中序遍历二叉树）：设 T 是一个二叉树，给定一个根节点（2）所示的二叉树。算法输出一个附加的树 A，按中序访问时之间又X树的所有结点。
    T1. [初始化：] 赋给 A 为根，开始结点设置 P ← T。
    T2. [P=A?] 如果 P=A，则转到步骤 T4。
    T3. [树 ← P.] 否则，P 指向的一个未访问过的非空二叉树，开始指向一个未访问过的非空二叉树，而 A←P，即把 P 的值赋给 A (见 2.2.1 节)。然后 P ← L.LINK(P)，并返回步骤 T2。
    T4. [P <= 树.] 如果树 A 为空，则算法终止；否则 P←A。
    T5. [P 访问.] 访问 NODE(P)。然后，置 P← R.LINK(P) 并返回步骤 T2。
    */

    /*
    stack<BiTree> s;
    BiTree p = T;
    while (p || !s.empty()) {
        if (p) {s.push(p); p = p->lchild;}
        else {
            s.pop();
            Visit(p->data);
            p = p->rchild
        }
    }
    return OK;
    */
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

Status CountLayerNodes(BiTree T, int currentLayer, int Layer, int maxDepth, int& count) {
    //合法性检验
    if (Layer < 1 || Layer > maxDepth) return ERROR;
    if (T == nullptr || currentLayer > Layer) return OK; // 剪枝,如果已经大于层次则可以不用再计算
    if (currentLayer == Layer) count++;
    CountLayerNodes(T->lchild, currentLayer + 1, Layer, maxDepth,count);
    CountLayerNodes(T->rchild, currentLayer + 1, Layer, maxDepth, count);
    return OK;
}

