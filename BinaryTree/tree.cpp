#include "BiTree.h"

int main()
{
	BiTree T;int count=0;

	printf("请按先序输入二叉树(如：AB00C00表示A为根结点、B为左孩子、C为右孩子的二叉树，其中0代表空格)：\n");
	CreateBiTree(T); // 建立二叉树T

    printf("先序遍历为：");
	PreOrderTraverse(T,visit);
	printf("\n中序遍历为：");
	InOrderTraverse(T,visit);
	printf("\n后序遍历为：");
	PostOrderTraverse(T,visit);
	printf("\n");

	printf("按目录形式输出二叉树：\n");
	PrintTree(T,1);

	CountLeaf(T,count);
    printf("二叉树的叶子结点个数是：%d\n",count);

    printf("二叉树的高度是：%d\n",TreeDepth (T));

	DestroyBiTree(T); // 销毁二叉树T
	return 1;
}

