 #include"public1.H"
 #include"linklist.h"

Status InitList(LinkList &L)
{
    // ����һ���յĵ�����L
    L=(LinkList)malloc(sizeof(LNode));
    if (!L)
        exit(OVERFLOW);
    L->next=NULL;
    return OK;
 }

Status DestroyList(LinkList &L)
{
    // ���ٵ�����L
    //�ȳ�������ͷ�ڵ�
    if (L == nullptr)
    {
        return OK; //������Ϊ��
    }

    LNode * current_node = L;
    LNode * next_node;

    while (current_node != nullptr) //��ʼ��������
    {
        next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }

    L = nullptr; //�ÿ�

    return OK;
}

void CreateList(LinkList &L,int n)
{
    // ��λ������n��Ԫ�ص�ֵ����������ͷ�ṹ�ĵ������Ա�L
    int i;
    LinkList p;
    L=(LinkList)malloc(sizeof(LNode));
    L->next=NULL;
    printf("������%d������\n",n);
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
    // ��λ������n��Ԫ�ص�ֵ����������ͷ�ṹ�ĵ������Ա�
    L = ( LNode *) malloc(sizeof(LNode));
    L->next = NULL;
    //����һ��βָ�룬������β�����в���
    LNode * tail_ptr = L; //��ʼ��Ϊͷ�ڵ�

    printf("������%d������\n", n);
    for (int i = 0; i < n; i++)
    {
        LNode * new_node =  ( LNode *) malloc(sizeof(LNode)); //Ϊ�½ڵ㴴���ڴ�ռ�

        scanf("%d", &new_node->data);
        new_node->next = nullptr;

        tail_ptr->next = new_node;
        tail_ptr = new_node;
    }
}

int ListLength(LinkList L)
{
    // ����L������Ԫ�ظ���
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
    nodes_count--; //��ȥͷ�ڵ�
    return nodes_count;
}

Status GetElem(LinkList L,int i,ElemType &e)
{
    // LΪ��ͷ���ĵ�������ͷָ�롣����i��Ԫ�ش���ʱ,��ֵ����e������OK,���򷵻� ERROR
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

LinkList GetElemPtr(LinkList L,int i)
{
    // LΪ��ͷ���ĵ�������ͷָ�롣����i��Ԫ�ش���ʱ,��ֵ����e������OK,���򷵻� ERROR
    int j=1;
    LinkList p=L->next;
    while(p&&j<i)
    {
        p=p->next;
        j++;
    }
    if(!p||j>i)
        return ERROR;
    return p;
 }

int LocateElem(LinkList L,ElemType e)
{
    // ����L�е�1��ֵΪe ������Ԫ�ص�λ��������������Ԫ�ز�����,�򷵻�ֵΪ0
    if (L == nullptr)
    {
        return ERROR; //��ֵ���
    }

    LNode * temp_ptr = L->next; //�ӵ�һ����Ч�ڵ㿪ʼ

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
    //��������������ĸ���Ԫ��ֵ
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
    //�ڴ�ͷ�ڵ�ĵ�����L�е�i��λ��֮ǰ����Ԫ��e
     // ���кϷ��Լ��
    if (i < 1 || i > ListLength(L) + 1 || L == nullptr)
    {
        return ERROR; // ����λ����Ч������Ϊ��
    }

    //�������ýڵ�
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
        return OVERFLOW; //�ڴ����ʧ��
    }

    new_node->data = e;
    new_node->next = travel_ptr->next;
    travel_ptr->next = new_node;

	return OK;
}

Status ListDelete(LinkList &L,int i,ElemType& e)
{
    //�ڴ�ͷ�ڵ�ĵ�����L�У�ɾ����i��Ԫ�أ�����e������ֵ
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
    //��֪���Ա�La��Lb�е�����Ԫ�ذ�ֵ�ǵݼ�����
    //�鲢La��Lb�õ��µ����Ա�Lc,Lc������Ԫ��Ҳ��ֵ�ǵݼ�����
    LNode * pa = La->next;
    LNode * pb = Lb->next;
    LNode * pc = La;
    Lc = La; //��La��ͷ�ڵ���ΪLc��ͷ�ڵ�

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
    pc->next = pa?pa:pb; //����ʣ���
    free(Lb);
}

//ʵ�ֹ鲢�㷨MergeList2��ʹ�ظ���Ԫ��ֻ����һ��
void MergeList2(LinkList &La, LinkList &Lb, LinkList &Lc)
{
    //��֪���Ա�La��Lb�е�����Ԫ�ذ�ֵ�ǵݼ�����
    //�鲢La��Lb�õ��µ����Ա�Lc,Lc������Ԫ��Ҳ��ֵ�ǵݼ�����
    LNode * pa = La->next;
    LNode * pb = Lb->next;
    LNode * pc = La;
    Lc = La; //��La��ͷ�ڵ���ΪLc��ͷ�ڵ�

    while (pa && pb)
    {
        if (pa->data < pb->data)
        {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else if (pa->data > pb->data)
        {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
        else //�������ֱ����Ҫ���߶����
        {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
            pb = pb->next;
        }
    }
    pc->next = pa?pa:pb; //����ʣ���
    free(Lb);
}

//�͵���ת
Status Reverse(LinkList &L)
{
    //����Ҫע���ͷ���Ĳ�һ��
    LinkList p = L;
    if (L->next == nullptr)
    {
        return ERROR; //�Ϸ��Լ�鿴�Ƿ��ǿձ�
    }
    LinkList q = L->next;
    LinkList r = q->next;
    while(q != nullptr)
    {
        r = q->next;
        if (p == L) //˵��λ�ڵ�һ�� ��ʱqΪ��һ����Ч�ڵ�
        {
            q->next = nullptr;
        }
        else
        {
            q->next = p;
        }
        p = q;
        q = r;
    }
    L->next = p; //����ͷ���

    return OK;
}

//ѡ����ʵ�ֵ�����ÿk���ڵ�һ����з�ת
Status ReverseAsGroup(LinkList &L, int k)
{
    int length = ListLength(L);
    int iteration = length / k;

    if (k > length)
    {
        return ERROR; //�Ϸ��Լ��
    }

    LinkList * heads = (LinkList *) malloc((iteration + 1) * sizeof(LinkList)); //��һ�������洢���������������һ�ֵ�ͷ���
    LinkList * tails = (LinkList *) malloc((iteration + 1) * sizeof(LinkList));
    //�����ҵ�ÿһ�ε�ͷ����β�ڵ�
    int heads_index = 0;
    int tails_index = 0;
    int nodes_count = 0;
    LinkList temp = L;
    while (temp != nullptr)
    {
        temp = temp->next;
        nodes_count++;
        if (temp != nullptr && (nodes_count - 1) % k == 0 && nodes_count <= (iteration * k)) //Ϊ��������ͷ���
        {
            heads[heads_index] = temp;
            heads_index++;
        }
        if (temp != nullptr && (nodes_count) % k == 0 && nodes_count <= (iteration * k)) //Ϊ��������β���
        {
            tails[tails_index] = temp;
            tails_index++;
        }
    }
    heads[heads_index] = GetElemPtr(L, k * iteration + 1); //���һ�η���k��β��
    tails[tails_index] = GetElemPtr(L, length);

    for (int i = 0; i < iteration; i++)
    {
        LinkList p = heads[i];
        LinkList q = p->next;
        LinkList r = q->next;

        while (p != tails[i])
        {
            r = q->next;
            q->next = p;
            p = q;
            q = r;
        }

        if (i == 0 && i != iteration - 1) //��һ���������Ҳ�Ϊ���һ��Ҫ��ת��������
        {
            L->next = tails[0];
            heads[0]->next = tails[1];
        }
        else if (i == 0 && i == iteration - 1)
        {
            L->next = tails[0];
            heads[0]->next = heads[1];
        }
        else if (i == iteration - 1)
        {
            heads[i]->next = heads[i + 1];
        }
        else
        {
            heads[i]->next = tails[i + 1];
        }
    }
    return OK;
}

int main()
{
    int n =5;
    LinkList Lb,La,Lc;
    InitList(Lb);
    printf("��λ��,");
    CreateList(Lb,n);
    printf("�����ĳ���Ϊ%d\n",ListLength(Lb));
    printf("����������Ϊ��");
    ListTraverse(Lb,print);
    ElemType e1;
    GetElem(Lb,2,e1);
    printf("��2��Ԫ�ص�ֵΪ:%d\n",e1);
    int index1 = LocateElem(Lb,e1);
    printf("ֵΪ%d��Ԫ���������е�λ����%d\n",e1,index1);
    DestroyList(Lb);
    printf("�����������������ĳ���Ϊ%d\n",ListLength(Lb));

    printf("\n");
    InitList(La);
    printf("��λ��,");
    CreateList2(La,n);
    printf("�����ĳ���Ϊ%d\n",ListLength(La));
    printf("����������Ϊ��");
    ListTraverse(La,print);
    ElemType e2;
    GetElem(La,2,e2);
    printf("��2��Ԫ�ص�ֵΪ:%d\n",e2);
    int index2 = LocateElem(La,e2);
    printf("ֵΪ%d��Ԫ���������е�λ����%d\n",e2,index2);
    DestroyList(La);
    printf("�����������������ĳ���Ϊ%d\n",ListLength(La));

    printf("\n");
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
    printf("�ϲ��������=");
    ListTraverse(Lc,print);

    ElemType e;
	ListDelete(Lc,2,e);
	printf("ɾ���Ľڵ�=%d\n",e);
    printf("ɾ���������=");
    ListTraverse(Lc,print);
    DestroyList(Lc);
    printf("�����������������ĳ���Ϊ%d\n\n",ListLength(Lc));

    //��ʼ��һ��La��������ԭ����ת
	InitList(La);
    for(j=1;j<=4;j++)
		ListInsert(La,j,a[j-1]);
    printf("�Ե��������о͵���ת������\n");
    printf("��תǰ��");
    ListTraverse(La, print);
    Reverse(La);
    printf("��ת��");
    ListTraverse(La, print);
    DestroyList(La);
    printf("�����������������ĳ���Ϊ%d\n\n",ListLength(La));

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

	MergeList2(La,Lb,Lc);
    printf("ȥ�غϲ��������=");
    ListTraverse(Lc,print);

    printf("\n");
    printf("׼����ʼ���Է��鷭ת������ѡ�񴴽���������\n");
    int test_n = 0;
    printf("������Ҫ����������Ԫ�ظ�����");
    scanf("%d", &test_n);
    CreateList2(La, test_n);
    printf("�����������£�");
    ListTraverse(La, print);
    int test_k = 0;
    printf("������k�Ĵ�С��");
    scanf("%d", &test_k);
    ReverseAsGroup(La, test_k);
    printf("���з��鷭ת��");
    ListTraverse(La, print);

   return 1;
 }