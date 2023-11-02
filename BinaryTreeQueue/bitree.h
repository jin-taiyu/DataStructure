
#include "public1.h"

typedef char TElemType;

//二叉树的二叉链表存储结构
/*typedef struct BiTNode{
	TElemType data; // 结点的值
	struct BiTNode *lchild,*rchild; // 左右孩子指针
}*BiTree;*/

#ifndef DEF

//二叉树的二叉链表存储结构。
typedef struct BiTNode{
	TElemType data; // 结点的值
	BiTNode *lchild,*rchild; // 左右孩子指针
}BiTNode,*BiTree;
#endif
#define DEF
//Status CreateBiTree(BiTree &T);
BiTree CreateTree(TElemType A[], TElemType B[],int ha,int la,int hb,int lb);/* 根据完全先序序列建立二叉树 */
void visit(TElemType e);
Status LevelOrderTraverse(BiTree T,void(*Visit)(TElemType));   /* 层次遍历二叉树 */
Status IsCompleteTree(BiTree T); /* 判断一棵二叉树是否是完全二叉树 */
Status PrintTree(BiTree bt, int nLayer);  /* 按竖向树状打印的二叉树 */
Status DestroyBiTree(BiTree &T); /* 销毁二叉树 */











