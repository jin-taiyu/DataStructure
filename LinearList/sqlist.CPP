#include"public1.H"
#include"sqlist.H"
Status InitList(SqList &L)
{
    //构造一个空的顺序表
    L.elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!L.elem)
        exit(OVERFLOW);
    L.length=0;
    L.listsize=LIST_INIT_SIZE;
    return OK;
}

Status DestroyList(SqList &L)
{ //销毁顺序线性表L

    return OK;
}

Status comp(ElemType c1, ElemType c2)
{
    if(c1==c2)
        return TRUE;
    else
        return FALSE;
}

int LocateElem(SqList L, ElemType e,Status (* compare)(ElemType, ElemType))
{ //根据数据元素的值，返回它在线性表L中的位置
    int i=0;
    while ((i<=L.length)&&(!compare(*(L.elem+i-1),e)))
        i++;
    if (i<=L.length)
        return i;
    else
    return(0);
}

Status GetElem(SqList L,int i,ElemType &e)
{ //根据数据元素在线性表L中的位置，返回它的值

    return OK;
}

Status ListInsert(SqList &L,int i,ElemType e)
{ // 在L中第i个位置之前插入新的数据元素e，L的长度加1

    return OK;
}

Status ListDelete(SqList &L,int i,ElemType &e)
{ //删除L的第i个数据元素，并用e返回其值，L的长度减1

    return OK;
}

void print(ElemType c)
{
    printf("%d ",c);
}

Status ListTraverse(SqList L,void(* visit)(ElemType))
{ //按序输出顺序表的各个元素值
    int i;
    for(i=1;i<=L.length;i++)
        visit(*(L.elem+i-1));
    cout<<endl;
    printf("L.elem=%u L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);
    return OK;
}


int main()
{
    //初始化线性表
    SqList L;
    ElemType e;
    Status i;
    int j;
    i=InitList(L);
    printf("初始化L后：*L.elem=");
    ListTraverse(L,print);

    //在表头插入数据
    for(j=1;j<=5;j++)
        i=ListInsert(L,1,j);
    printf("在L的表头依次插入1～5后：*L.elem=");
    ListTraverse(L,print);

    //在表尾插入数据
    for(j=1;j<=5;j++)
        *(L.elem+L.length+j-1)=j;
    printf("在L的表尾依次插入1～5后：*L.elem=");
    L.length=L.length+5;
    ListTraverse(L,print);

    //测试栈溢出
    ListInsert(L,1,0);
    printf("在L的表头插入0后：*L.elem=");
    ListTraverse(L,print);

    //测试查询元素位置
    i=LocateElem(L,1,comp);
    printf("值为1的数据元素在顺序表中的位置是");
    printf("%d \n",i);

    //测试
    GetElem(L,5,e);
    printf("第5个元素的值为：%d\n",e);

    //测试删除元素
    printf("在L中删除第3个数据元素：*L.elem=");
    ListDelete(L,3,e);
    ListTraverse(L,print);

    //测试销毁表
    DestroyList(L);
    printf("销毁L后：L.elem=%u L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);
    return 1;
}
