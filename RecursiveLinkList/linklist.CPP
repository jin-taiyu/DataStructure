#include"public1.H"
#include"linklist.h"

Status InitList(LinkList &L)
{
    // 构造一个空的单链表L
    L=(LinkList)malloc(sizeof(LNode));
    if (!L)
        exit(OVERFLOW);
    L->next=NULL;
    return OK;
}

void createList(LinkList &p)
{
    // 递归新建单链表
    ElemType e;
    printf("请每行输入一个数据元素并按回车(直到-1退出)：\n");

    scanf("%d", &e);
    //退出条件
    if (e == -1)
    {
        p = nullptr; //不要忘记尾结点指向置空 调试半天才发现
        return;
    }
    //进入递归
    else
    {
        p = (LinkList)malloc(sizeof(LNode)); // 分配新节点
        p->data = e;
        createList(p->next); // 递归创建下一个节点
    }
}

int ListLength(LinkList L)
{
    // 初始条件：线性表L已存在。操作结果：递归实现求表长
    if (L == nullptr)
    {
        return 0;
    }
    else
    {
        return ListLength(L->next) + 1;
    }

}

LinkList MergeList(LinkList pa,LinkList pb)
{
    //递归实现两个有序单链表的归并
    //递归终止条件
    //若第一个链表已经遍历完了 剩下的元素都在 pb 中 不需要再进行合并 直接返回
    if (pa == nullptr) {
        return pb;
    }
    //同理
    if (pb == nullptr) {
        return pa;
    }

    //尝试过原址归并发现有难度
    //于是采用额外空间实现
    LinkList mergedList = NULL;

    if (pa->data <= pb->data) {
        mergedList = pa;
        mergedList->next = MergeList(pa->next, pb);
    } else {
        mergedList = pb;
        mergedList->next = MergeList(pa, pb->next);
    }

    return mergedList;
}


Status ListTraverse(LinkList &L)
{
    // 递归实现单链表的输出
    if (L == nullptr) //特殊情况空表直接返回
    {
        return ERROR;
    }

    if (L->next == nullptr)
    {
        return OK;
    }
    else
    {
        printf("%d ", (L->next)->data);
        ListTraverse(L->next);
        return OK;
    }
}

int main()
{
    LinkList La,Lb,Lc,Ld;
    InitList(La); // 创建空表La

    createList(La->next);
    printf("La= "); // 输出表La的内容
    ListTraverse(La);
    printf("\n");

    InitList(Lb); // 创建空表Lb
    createList(Lb->next);
    printf("Lb= "); // 输出表Lb的内容
    ListTraverse(Lb);
    printf("\n");

    if (La==NULL||Lb==NULL)
        printf("没有表结构无法归并");
    LinkList pa=La->next;
    LinkList pb=Lb->next;
    LinkList pc=MergeList(pa,pb);
    Lc=(LinkList)malloc(sizeof(LNode));
    Lc->next=pc;
    printf("归并后的链表= "); // 输出表Lc的内容
    ListTraverse(Lc);
    printf("\n归并后的链表长度=%d\n",ListLength(Lc)); // 输出删除的元素


    printf("\n逆置后的链表= "); // 输出表逆置后Lc的内容
    ListTraverse(Lc);
    printf("\n");
    return 1;
}
