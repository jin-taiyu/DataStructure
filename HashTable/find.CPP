 #include"public1.H"
 #include"hash.h"

 //初始化哈希表
 Status InitHashTable(HashTable &H) {
     // 操作结果: 构造一个空的哈希表
    int i;
    H.count=0; // 当前元素个数为0
    H.sizeindex=0; // 初始存储容量为hashsize[0]
    m=hashsize[0];
    H.elem=(ElemType*)malloc(m*sizeof(ElemType));
    if(!H.elem)
        exit(OVERFLOW); // 存储分配失败
    for(i=0;i<m;i++)
        H.elem[i].key=NULLKEY; // 未填记录的标志
    return OK;
}

void DestroyHashTable(HashTable &H)
{
    // 初始条件: 哈希表H存在。操作结果: 销毁哈希表H
    free(H.elem);
    H.elem=NULL;
    H.count=0;
    H.sizeindex=0;
}

unsigned Hash(KeyType K) {
    // 一个简单的哈希函数(m为表长，全局变量)
    // 使用简单的模运算作为哈希函数
    extern int m;
    return K % m;
}

 void collision(int &p,int d)  {
     // 线性探测再散列
     // 开放定址法处理冲突
    // 公式Hi=(H(key)+di)MOD m
    extern int m;
    // 对公式做了一定程度的修改
    // 对m取余确保不越界
    p = (p + 1) % m;
}

Status SearchHash(HashTable H,KeyType K,int &p,int &c) {
     // 在开放定址哈希表H中查找关键码为K的元素,若查找成功,以p指示待查数据
    // 元素在表中位置,并返回SUCCESS;否则,以p指示插入位置,并返回UNSUCCESS
    // c用以计冲突次数，其初值置零，供建表插入时参考。算法9.17
    p = Hash(K);
    // 当该位置填有数据但关键字不相等时
    // 意味着出现冲突
    while (H.elem[p].key != NULLKEY && !EQ(K, H.elem[p].key))
        collision(p, ++c);
    if (EQ(K, H.elem[p].key))
        return SUCCESS;
    else return UNSUCCESS;
}

Status InsertHash(HashTable &,ElemType); // 对函数的声明


void RecreateHashTable(HashTable &H) {
    // 重建哈希表
    // 重建哈希表
    int i,count=H.count;
    ElemType *p,*elem=(ElemType*)malloc(count*sizeof(ElemType));
    p=elem;
    printf("重建哈希表\n");
    for(i=0;i<m;i++) // 保存原有的数据到elem中
        if((H.elem+i)->key!=NULLKEY) // 该单元有数据
        *p++=*(H.elem+i);
    H.count=0;
    H.sizeindex++; // 增大存储容量
    m=hashsize[H.sizeindex];
    p=(ElemType*)realloc(H.elem,m*sizeof(ElemType));
    if(!p)
        exit(OVERFLOW); // 存储分配失败
    H.elem=p;
    for(i=0;i<m;i++)
        H.elem[i].key=NULLKEY; // 未填记录的标志(初始化)
    for(p=elem;p<elem+count;p++) // 将原有的数据按照新的表长插入到重建的哈希表中
        InsertHash(H,*p);
}

Status InsertHash(HashTable &H,ElemType e) {
    // 查找不成功时插入数据元素e到开放定址哈希表H中，并返回OK；
    // 若冲突次数过大，则重建哈希表，算法9.18
    int c = 0;
    int p = Hash(e.key);
    // 表中已有与e相同关键字的元素
    if (SearchHash(H, e.key, p, c))
        return DUPLICATE;
    // 冲突次数c未达到上限
    else if (c < hashsize[H.sizeindex] / 2) {
        H.elem[p] = e;
        ++H.count;
        return OK;
    }
    else {RecreateHashTable(H); return UNSUCCESS;}
}

void TraverseHash(HashTable H,void(*Vi)(int,ElemType)) {
    // 按哈希地址的顺序遍历哈希表
    printf("哈希地址0～%d\n",m-1);
    for (int i = 0; i < m; i++) {
        if (H.elem[i].key != NULLKEY) {
                Vi(i, H.elem[i]);
        }
    }
}


void print(int p,ElemType r) {
    printf("address=%d (%d,%d)\n",p,r.key,r.ord);
}

int main() {
    ElemType r[N]={{17,1},{60,2},{29,3},{38,4},{1,5},{2,6},{3,7},{4,8},{60,9},{13,10}};
    HashTable h;
    int i,p;
    Status j;
    KeyType k;
    InitHashTable(h);
    int c=0;
    for(i=0;i<N-1;i++)
    { // 插入前N-1个记录
        j=InsertHash(h,r[i]);
        if(j==DUPLICATE)
            printf("表中已有关键字为%d的记录，无法再插入记录(%d,%d)\n",r[i].key,r[i].key,r[i].ord);
    }
    printf("按哈希地址的顺序遍历哈希表:\n");
    TraverseHash(h,print);
    printf("请输入待查找记录的关键字: ");
    scanf("%d",&k);
    j=SearchHash(h,k,p,c);
    if(j==SUCCESS)
        print(p,h.elem[p]);
    else
        printf("没找到\n");
    j=InsertHash(h,r[i]); // 插入第N个记录
    if(j==ERROR) // 重建哈希表
        j=InsertHash(h,r[i]); // 重建哈希表后重新插入
    printf("按哈希地址的顺序遍历重建后的哈希表:\n");
    TraverseHash(h,print);
    printf("请输入待查找记录的关键字: ");
    scanf("%d",&k);
    c=0;
    j=SearchHash(h,k,p,c);
    if(j==SUCCESS)
        print(p,h.elem[p]);
    else
        printf("没找到\n");
    DestroyHashTable(h);

    return 1;
}
