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

void createList(LinkList &p)
{
    // �ݹ��½�������
    ElemType e;
    printf("��ÿ������һ������Ԫ�ز����س�(ֱ��-1�˳�)��\n");

    scanf("%d", &e);
    //�˳�����
    if (e == -1)
    {
        p = nullptr; //��Ҫ����β���ָ���ÿ� ���԰���ŷ���
        return;
    }
    //����ݹ�
    else
    {
        p = (LinkList)malloc(sizeof(LNode)); // �����½ڵ�
        p->data = e;
        createList(p->next); // �ݹ鴴����һ���ڵ�
    }
}

int ListLength(LinkList L)
{
    // ��ʼ���������Ա�L�Ѵ��ڡ�����������ݹ�ʵ�������
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
    //�ݹ�ʵ���������������Ĺ鲢
    //�ݹ���ֹ����
    //����һ�������Ѿ��������� ʣ�µ�Ԫ�ض��� pb �� ����Ҫ�ٽ��кϲ� ֱ�ӷ���
    if (pa == nullptr) {
        return pb;
    }
    //ͬ��
    if (pb == nullptr) {
        return pa;
    }

    //���Թ�ԭַ�鲢�������Ѷ�
    //���ǲ��ö���ռ�ʵ��
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
    // �ݹ�ʵ�ֵ����������
    if (L == nullptr) //��������ձ�ֱ�ӷ���
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
    InitList(La); // �����ձ�La

    createList(La->next);
    printf("La= "); // �����La������
    ListTraverse(La);
    printf("\n");

    InitList(Lb); // �����ձ�Lb
    createList(Lb->next);
    printf("Lb= "); // �����Lb������
    ListTraverse(Lb);
    printf("\n");

    if (La==NULL||Lb==NULL)
        printf("û�б��ṹ�޷��鲢");
    LinkList pa=La->next;
    LinkList pb=Lb->next;
    LinkList pc=MergeList(pa,pb);
    Lc=(LinkList)malloc(sizeof(LNode));
    Lc->next=pc;
    printf("�鲢�������= "); // �����Lc������
    ListTraverse(Lc);
    printf("\n�鲢�����������=%d\n",ListLength(Lc)); // ���ɾ����Ԫ��


    printf("\n���ú������= "); // ��������ú�Lc������
    ListTraverse(Lc);
    printf("\n");
    return 1;
}