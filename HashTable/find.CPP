 #include"public1.H"
 #include"hash.h"

 //��ʼ����ϣ��
 Status InitHashTable(HashTable &H) {
     // �������: ����һ���յĹ�ϣ��
    int i;
    H.count=0; // ��ǰԪ�ظ���Ϊ0
    H.sizeindex=0; // ��ʼ�洢����Ϊhashsize[0]
    m=hashsize[0];
    H.elem=(ElemType*)malloc(m*sizeof(ElemType));
    if(!H.elem)
        exit(OVERFLOW); // �洢����ʧ��
    for(i=0;i<m;i++)
        H.elem[i].key=NULLKEY; // δ���¼�ı�־
    return OK;
}

void DestroyHashTable(HashTable &H)
{
    // ��ʼ����: ��ϣ��H���ڡ��������: ���ٹ�ϣ��H
    free(H.elem);
    H.elem=NULL;
    H.count=0;
    H.sizeindex=0;
}

unsigned Hash(KeyType K) {
    // һ���򵥵Ĺ�ϣ����(mΪ������ȫ�ֱ���)
    // ʹ�ü򵥵�ģ������Ϊ��ϣ����
    extern int m;
    return K % m;
}

 void collision(int &p,int d)  {
     // ����̽����ɢ��
     // ���Ŷ�ַ��������ͻ
    // ��ʽHi=(H(key)+di)MOD m
    extern int m;
    // �Թ�ʽ����һ���̶ȵ��޸�
    // ��mȡ��ȷ����Խ��
    p = (p + 1) % m;
}

Status SearchHash(HashTable H,KeyType K,int &p,int &c) {
     // �ڿ��Ŷ�ַ��ϣ��H�в��ҹؼ���ΪK��Ԫ��,�����ҳɹ�,��pָʾ��������
    // Ԫ���ڱ���λ��,������SUCCESS;����,��pָʾ����λ��,������UNSUCCESS
    // c���ԼƳ�ͻ���������ֵ���㣬����������ʱ�ο����㷨9.17
    p = Hash(K);
    // ����λ���������ݵ��ؼ��ֲ����ʱ
    // ��ζ�ų��ֳ�ͻ
    while (H.elem[p].key != NULLKEY && !EQ(K, H.elem[p].key))
        collision(p, ++c);
    if (EQ(K, H.elem[p].key))
        return SUCCESS;
    else return UNSUCCESS;
}

Status InsertHash(HashTable &,ElemType); // �Ժ���������


void RecreateHashTable(HashTable &H) {
    // �ؽ���ϣ��
    // �ؽ���ϣ��
    int i,count=H.count;
    ElemType *p,*elem=(ElemType*)malloc(count*sizeof(ElemType));
    p=elem;
    printf("�ؽ���ϣ��\n");
    for(i=0;i<m;i++) // ����ԭ�е����ݵ�elem��
        if((H.elem+i)->key!=NULLKEY) // �õ�Ԫ������
        *p++=*(H.elem+i);
    H.count=0;
    H.sizeindex++; // ����洢����
    m=hashsize[H.sizeindex];
    p=(ElemType*)realloc(H.elem,m*sizeof(ElemType));
    if(!p)
        exit(OVERFLOW); // �洢����ʧ��
    H.elem=p;
    for(i=0;i<m;i++)
        H.elem[i].key=NULLKEY; // δ���¼�ı�־(��ʼ��)
    for(p=elem;p<elem+count;p++) // ��ԭ�е����ݰ����µı������뵽�ؽ��Ĺ�ϣ����
        InsertHash(H,*p);
}

Status InsertHash(HashTable &H,ElemType e) {
    // ���Ҳ��ɹ�ʱ��������Ԫ��e�����Ŷ�ַ��ϣ��H�У�������OK��
    // ����ͻ�����������ؽ���ϣ�����㷨9.18
    int c = 0;
    int p = Hash(e.key);
    // ����������e��ͬ�ؼ��ֵ�Ԫ��
    if (SearchHash(H, e.key, p, c))
        return DUPLICATE;
    // ��ͻ����cδ�ﵽ����
    else if (c < hashsize[H.sizeindex] / 2) {
        H.elem[p] = e;
        ++H.count;
        return OK;
    }
    else {RecreateHashTable(H); return UNSUCCESS;}
}

void TraverseHash(HashTable H,void(*Vi)(int,ElemType)) {
    // ����ϣ��ַ��˳�������ϣ��
    printf("��ϣ��ַ0��%d\n",m-1);
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
    { // ����ǰN-1����¼
        j=InsertHash(h,r[i]);
        if(j==DUPLICATE)
            printf("�������йؼ���Ϊ%d�ļ�¼���޷��ٲ����¼(%d,%d)\n",r[i].key,r[i].key,r[i].ord);
    }
    printf("����ϣ��ַ��˳�������ϣ��:\n");
    TraverseHash(h,print);
    printf("����������Ҽ�¼�Ĺؼ���: ");
    scanf("%d",&k);
    j=SearchHash(h,k,p,c);
    if(j==SUCCESS)
        print(p,h.elem[p]);
    else
        printf("û�ҵ�\n");
    j=InsertHash(h,r[i]); // �����N����¼
    if(j==ERROR) // �ؽ���ϣ��
        j=InsertHash(h,r[i]); // �ؽ���ϣ�������²���
    printf("����ϣ��ַ��˳������ؽ���Ĺ�ϣ��:\n");
    TraverseHash(h,print);
    printf("����������Ҽ�¼�Ĺؼ���: ");
    scanf("%d",&k);
    c=0;
    j=SearchHash(h,k,p,c);
    if(j==SUCCESS)
        print(p,h.elem[p]);
    else
        printf("û�ҵ�\n");
    DestroyHashTable(h);

    return 1;
}