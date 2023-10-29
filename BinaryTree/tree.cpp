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

    int desiredLayer;
    int countLayer = 0;
    int depth = TreeDepth(T);
    cout << "请输入要计算结点数的层次：" << endl;
    cin >> desiredLayer;
    CountLayerNodes(T, 1, desiredLayer, depth, countLayer);
    cout << "第" << desiredLayer << "层的结点数为：" << countLayer << endl;

    // 用这种方法创建的map中并不存在根节点父节点的映射
    // 非常巧妙的避开了题目中需要判断的根节点问题
    // 而且听说map的寻找复杂度为lgn
    // 比单独遍历节点创建额外数组的线性阶要快
    map<char, char> parents;
    // 打表 直接把所有的父节点算出来
    FindParentNode(T, parents);
    char desiredNode;
    cout << "请输入要查找父结点的结点：" << endl;
    cin >> desiredNode;
    if (parents[desiredNode]) {
        cout << desiredNode << "的父结点为" << parents[desiredNode] << endl;
    }
    else {
        cout << "输入为根节点或不存在的节点！" << endl;
    }

    // 求所有祖先即为求父节点、父节点的父节点......
    // 我们可以直接借助上一问中的map
    // 但题目要求编写算法
    // 我们直接建立另外一个函数
    cout << "请输入要查找祖先结点的结点：" << endl;
    char desiredAnstNode;
    cin >> desiredAnstNode;
    int ans = FindAncestors(T, parents, desiredAnstNode);
    if (!ans) cout << "输入为根节点或不存在的节点！";

	DestroyBiTree(T); // 销毁二叉树T
	return 1;
}

