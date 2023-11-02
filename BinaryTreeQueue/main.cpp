#include "BiTree.h"

int main()
{
    BiTree T;

    int ha=0;  int la=8;
	int hb=0;  int lb=8;
	TElemType A[9]={'A','B','C','D','E','F','G','H','K'};
    TElemType B[9]={'B','D','C','A','E','H','G','K','F'};

	T=CreateTree(A,B,ha,la,hb,lb);// 建立二叉树T*/

	printf("二叉树的层次遍历序列：\n");
	LevelOrderTraverse(T,visit);
	printf("\n");

	printf("按目录形式输出二叉树：\n");
	PrintTree(T,0);

        if (IsCompleteTree(T))
        printf("这是一棵完全二叉树\n");
	else
        printf("这不是一棵完全二叉树\n");

    TElemType findElem;
    TElemType findResult;
	cout << "请输入要查找双亲的结点:"  << endl;
	cin >> findElem;
	if (FindParent(T, findElem, findResult)) {
        cout << findElem << "的父结点为" << findResult << endl;
	}
	else {
        cout << "输入根节点或不存在的节点" << endl;
	}

    TElemType nodeFirst;
    TElemType nodeSecond;
    TElemType nearAncestor;
    map<TElemType, TElemType> parents;
    cout << "请输入要查找最近祖先的两个结点(A B):" << endl;
    cin >> nodeFirst >> nodeSecond;
    if (FindNearAncestors(T, parents, nodeFirst, nodeSecond, nearAncestor)) {
        cout << nodeFirst << "与" << nodeSecond << "最近的共同祖先为" << nearAncestor << endl;
    }
    else {
        cout << "两者可能并没有共同祖先" << endl;
    }
	DestroyBiTree(T); // 销毁二叉树T
	return 1;
}

