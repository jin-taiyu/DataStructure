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

	DestroyBiTree(T); // 销毁二叉树T
	return 1;
}

