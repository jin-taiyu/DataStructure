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

Status DestroyList(LinkList &L)
{
    // 销毁单链表L
    //先尝试销毁头节点
    if (L == nullptr)
    {
        return OK; //链表已为空
    }

    LNode * current_node = L;
    LNode * next_node;

    while (current_node != nullptr) //开始遍历链表
    {
        next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }

    L = nullptr; //置空

    return OK;
}

void CreateList(LinkList &L,int n)
{
    // 逆位序输入n个元素的值，建立带表头结构的单链线性表L
    int i;
    LinkList p;
    L=(LinkList)malloc(sizeof(LNode));
    L->next=NULL;
    printf("请输入%d个数据\n",n);
    for(i=n;i>0;--i)
    {
        p=(LinkList)malloc(sizeof(LNode));
        scanf("%d",&p->data);
        p->next=L->next;
        L->next=p;
    }
}

void CreateList2(LinkList &L,int n)
{
    // 正位序输入n个元素的值，建立带表头结构的单链线性表
    L = ( LNode *) malloc(sizeof(LNode));
    L->next = NULL;
    //建立一个尾指针，用来在尾部进行插入
    LNode * tail_ptr = L; //初始化为头节点

    printf("请输入%d个数据\n", n);
    for (int i = 0; i < n; i++)
    {
        LNode * new_node =  ( LNode *) malloc(sizeof(LNode)); //为新节点创建内存空间

        scanf("%d", &new_node->data);
        new_node->next = nullptr;

        tail_ptr->next = new_node;
        tail_ptr = new_node;
    }
}

int ListLength(LinkList L)
{
    // 返回L中数据元素个数
    if (L == nullptr)
    {
        return 0;
    }
    LNode * temp_ptr = L;
    int nodes_count = 0;

    while (temp_ptr != nullptr)
    {
        temp_ptr = temp_ptr->next;
        nodes_count++;
    }
    nodes_count--; //减去头节点
    return nodes_count;
}

Status GetElem(LinkList L,int i,ElemType &e)
{
    // L为带头结点的单链表的头指针。当第i个元素存在时,其值赋给e并返回OK,否则返回 ERROR
    int j=1;
    LinkList p=L->next;
    while(p&&j<i)
    {
        p=p->next;
        j++;
    }
    if(!p||j>i)
        return ERROR;
    e=p->data;
    return OK;
 }

int LocateElem(LinkList L,ElemType e)
{
    // 返回L中第1个值为e 的数据元素的位序，若这样的数据元素不存在,则返回值为0
    if (L == nullptr)
    {
        return ERROR; //空值检查
    }

    LNode * temp_ptr = L->next; //从第一个有效节点开始

    int index = 1;
    while (temp_ptr != nullptr)
    {
        if (temp_ptr->data == e)
        {
            return index;
        }
        temp_ptr = temp_ptr->next;
        index++;
    }
    return 0;
}

 void print(ElemType c)
{
    printf("%d ",c);
}

Status ListTraverse(LinkList L,void(*visit)(ElemType))
{
    //按序输出单链表的各个元素值
    LinkList p=L->next;
    while(p)
    {
        visit(p->data);
        p=p->next;
    }
    printf("\n");
    return OK;
}

Status ListInsert(LinkList &L,int i,ElemType e)
{
    //在带头节点的单链表L中第i个位置之前插入元素e
     // 进行合法性检查
    if (i < 1 || i > ListLength(L) + 1 || L == nullptr)
    {
        return ERROR; // 插入位置无效或链表为空
    }

    //遍历到该节点
    LNode * travel_ptr = L;
    int travel_index = 0;

    while (travel_ptr != nullptr && travel_index < i - 1)
    {
        travel_ptr = travel_ptr->next;
        travel_index++;
    }

    LNode * new_node = (LNode *) malloc(sizeof(LNode));
    if (new_node == nullptr)
    {
        return OVERFLOW; //内存分配失败
    }

    new_node->data = e;
    new_node->next = travel_ptr->next;
    travel_ptr->next = new_node;

	return OK;
}

Status ListDelete(LinkList &L,int i,ElemType& e)
{
    //在带头节点的单链表L中，删除第i个元素，并由e返回其值
    LNode * index = L;
    int j = 0;

    while(index->next && j < i - 1)
    {
        index = index->next;
        j++;
    }

    if (!(index->next) || j > i - 1)
    {
        return ERROR;
    }

    LNode * to_delete = index->next;
    index->next = to_delete->next;

    e = to_delete->data;
    free(to_delete);
    return OK;
}

void MergeList(LinkList &La, LinkList &Lb, LinkList &Lc)
{
    //已知线性表La和Lb中的数据元素按值非递减排列
    //归并La和Lb得到新的线性表Lc,Lc的数据元素也按值非递减排列
    LNode * pa = La->next;
    LNode * pb = Lb->next;
    LNode * pc = La;
    Lc = La; //用La的头节点作为Lc的头节点

    while (pa && pb)
    {
        if (pa->data <= pb->data)
        {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else
        {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }
    pc->next = pa?pa:pb; //插入剩余段
    free(Lb);
}

//实现归并算法MergeList2，使重复的元素只保存一次


int main()
{
    int n =5;
    LinkList Lb,La,Lc;
    InitList(Lb);
    printf("逆位序,");
    CreateList(Lb,n);
    printf("链表的长度为%d\n",ListLength(Lb));
    printf("链表的内容为：");
    ListTraverse(Lb,print);
    ElemType e1;
    GetElem(Lb,2,e1);
    printf("第2个元素的值为:%d\n",e1);
    int index1 = LocateElem(Lb,e1);
    printf("值为%d的元素在链表中的位置是%d\n",e1,index1);
    DestroyList(Lb);
    printf("销毁链表，该链表的长度为%d\n",ListLength(Lb));

    printf("\n");
    InitList(La);
    printf("正位序,");
    CreateList2(La,n);
    printf("链表的长度为%d\n",ListLength(La));
    printf("链表的内容为：");
    ListTraverse(La,print);
    ElemType e2;
    GetElem(La,2,e2);
    printf("第2个元素的值为:%d\n",e2);
    int index2 = LocateElem(La,e2);
    printf("值为%d的元素在链表中的位置是%d\n",e2,index2);

    DestroyList(La);
    printf("销毁链表，该链表的长度为%d\n",ListLength(La));


    int j, a[4]={3,5,8,11}, b[7]={2,6,8,9,11,15,20};
	InitList(La);
    for(j=1;j<=4;j++)
		ListInsert(La,j,a[j-1]);
	printf("La=");
    ListTraverse(La,print);

    InitList(Lb);
    for(j=1;j<=7;j++)
		ListInsert(Lb,j,b[j-1]);
	printf("Lb=");
    ListTraverse(Lb,print);

	MergeList(La,Lb,Lc);
    printf("合并后的链表=");
    ListTraverse(Lc,print);

    ElemType e;
	ListDelete(Lc,2,e);
	printf("删除的节点=%d\n",e);
    printf("删除后的链表=");
    ListTraverse(Lc,print);
    DestroyList(Lc);
    printf("销毁链表，该链表的长度为%d\n",ListLength(Lc));

   return 1;
 }
