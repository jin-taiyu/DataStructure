#include <iostream>
#include <vector>
#include <iomanip>

#include"public1.H"
#include"sqlist.H"

using namespace std;

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
{
    //销毁顺序线性表L
    if (L.elem)
    {
        free(L.elem);
        L.elem = NULL;
        L.length = 0;
        L.listsize = 0;
    }
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
{
    //根据数据元素的值，返回它在线性表L中的位置
    int i=0;
    while ((i<=L.length)&&(!compare(*(L.elem+i-1),e)))
        i++;
    if (i<=L.length)
        return i;
    else
    return(0);
}

Status GetElem(SqList L,int i,ElemType &e)
{
    //根据数据元素在线性表L中的位置，返回它的值
    if (i < 1 || i > L.length)
    {
        return ERROR;
    }
    e = L.elem[i - 1];
    return OK;
}

Status ListInsert(SqList &L,int i,ElemType e)
{
    // 在L中第i个位置之前插入新的数据元素e，L的长度加1
    if (i < 1 || i > L.length + 1)
    {
        return ERROR;
    }

    if (L.length >= L.listsize) //表满但仍插入会造成溢出
    {
        //重新分配空间
        ElemType * newbase = (ElemType *) realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)
        {
            return OVERFLOW;
        }
        L.elem = newbase;
        L.listsize = L.listsize + LISTINCREMENT;
    }

    //尝试插入
    ElemType * insert_index = L.elem + i - 1;

   // 从后往前移动元素以空出位置
    for (ElemType *p = &(L.elem[L.length - 1]); p >= insert_index; p--)
    {
        *(p + 1) = *p;
    }

    *insert_index = e;
    L.length++;

    return OK;
}

Status ListDelete(SqList &L,int i,ElemType &e)
{
    //删除L的第i个数据元素，并用e返回其值，L的长度减1
    //检查是否越界
    if (i < 1 || i > L.length)
    {
        return ERROR;
    }

    for (ElemType * p = &L.elem[i - 1]; p <= &L.elem[L.length - 2]; p++)
    {
        *p = *(p + 1);
    }

    L.length--; //表长减少

    return OK;
}

void print(ElemType c)
{
    printf("%d ",c);
}

Status ListTraverse(SqList L,void(* visit)(ElemType))
{
    //按序输出顺序表的各个元素值
    int i;
    for(i=1;i<=L.length;i++)
        visit(*(L.elem+i-1));
    cout<<endl;
    printf("L.elem=%u L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);
    return OK;
}

Status PriorElem(SqList L,ElemType cur_e,ElemType &pre_e)
 {
     // 若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱
     // 则操作失败
     if (cur_e == L.elem[0]) //确保不是第一个
     {
         return ERROR;
     }

     for (int i = 1; i < L.length; i++)
     {
         if (L.elem[i] == cur_e)
         {
             pre_e = L.elem[i - 1]; //在这里已经确保不会越界
             return OK;
         }
     }
     return ERROR; //未找到
 }

 Status DeleteAllX(SqList &L, ElemType x)
 {
     int valid_index = 0;
     for (int i = 0; i < L.length; i++)
     {
         if (L.elem[i] != x)
         {
             L.elem[valid_index] = L.elem[i];
             valid_index++;
         }
     }
     L.length = valid_index;
     return OK;
 }

int main(int argc, char *argv[])
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

    //测试查询前驱元素
    int test_curent_element = 0;
    int test_prior_element = 0;
    printf("\n\n**测试查询前驱元素**\n");
    printf("请输入要查询的元素：");
    scanf("%d", &test_curent_element);
    if (PriorElem(L, test_curent_element, test_prior_element))
    {
        printf("您输入的元素前驱为：%d\n", test_prior_element);
    }
    else{
        printf("错误！请尝试重新输入！\n");
    }

    //测试删除所有指定元素
    int test_to_delete_element = 0;
    printf("\n\n**测试删除所有指定元素**\n");
    printf("请输入要删除的元素：");
    scanf("%d", &test_to_delete_element);
    DeleteAllX(L, test_to_delete_element);
    printf("删除所有的%d之后：", test_to_delete_element);
    ListTraverse(L,print);

    //测试销毁表
    DestroyList(L);
    printf("销毁L后：L.elem=%u L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);

    return 1;
}
