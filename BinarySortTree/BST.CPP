// ��̬���ұ�(����������)�Ļ�������(8��)
#include"BiTree.h"
#include"public1.h"
#include"BST.h"


Status InitDSTable(BiTree &DT) {
    // �������: ����һ���յĶ�̬���ұ�DT
    DT=NULL;
    return OK;
}

void DestroyDSTable(BiTree &DT) {
    // ��ʼ����: ��̬���ұ�DT���ڡ��������: ���ٶ�̬���ұ�DT
    if(DT) {
        // �ǿ���
        if(DT->lchild) // ������
            DestroyDSTable(DT->lchild); // ������������
        if(DT->rchild) // ���Һ���
            DestroyDSTable(DT->rchild); // �����Һ�������
        free(DT); // �ͷŸ����
        DT=NULL; // ��ָ�븳0
    }
}

BiTree SearchBST(BiTree T,KeyType key) {
    // �ڸ�ָ��T��ָ�����������еݹ�ز���ĳ�ؼ��ֵ���key������Ԫ�أ�
    // �����ҳɹ����򷵻�ָ�������Ԫ�ؽ���ָ��,���򷵻ؿ�ָ�롣�㷨9.5(a)
    if ((!T) || EQ(key, T->data.key)) return(T);
    else if (LT(key, T->data.key)) return(SearchBST(T->lchild, key));
    else return(SearchBST(T->rchild, key));
}

void SearchBST(BiTree &T,KeyType key,BiTree f,BiTree &p,Status &flag) {
    // �㷨9.5(b)��
    // �ڸ�ָ��T��ָ�����������еݹ�ز�����ؼ��ֵ���key������Ԫ�أ�������
    // �ɹ�����ָ��pָ�������Ԫ�ؽ�㣬������TRUE������ָ��pָ�����·����
    // ���ʵ����һ����㲢����FALSE,ָ��fָ��T��˫�ף����ʼ����ֵΪNULL
    if (!T) {p = f; flag = FALSE; return;}
    else if (EQ(key, T->data.key)) {p = T; flag = TRUE; return;}
    else if (LT(key, T->data.key)) {SearchBST(T->lchild, key, T, p, flag);}
    else {SearchBST(T->rchild, key, T, p, flag);}
}

Status InsertBST(BiTree &T, ElemType e) {
    // ������������T�в����ڹؼ��ֵ���e.key������Ԫ��ʱ������e������TRUE��
    // ���򷵻�FALSE���㷨9.6(��)
    BiTree p = nullptr;
    Status flag = FALSE;
    SearchBST(T, e.key, nullptr, p, flag);
    if (!flag) {
        BiTree s = (BiTree) malloc(sizeof(BiTNode));
        s->data = e;
        s->lchild = s->rchild= nullptr;
        if (!p) T = s;
        else if (LT(e.key, p->data.key)) p->lchild = s;
        else p->rchild = s;
        return TRUE;
    }
    else return FALSE;
}

void Delete(BiTree &p) {
    // �Ӷ�����������ɾ�����p�����ؽ�����������������㷨9.8
    BiTree q = nullptr;
    BiTree s = nullptr;
    if (!p->rchild) { //����������ֻ��Ҫ�ؽ�����������
        q = p;
        p = p->lchild;
        free(q);
    }
    else if (!p->lchild) { //ֻ��Ҫ�ؽ�����������
        q = p;
        p = p->rchild;
        free(q);
    }
    else { //��������������
        q = p;
        s = p->lchild;
        while (s->rchild) {q = s; s = s->rchild;} //ת��Ȼ�������ߵ���ͷ
        p->data = s->data;
        if (q != p) q->rchild = s->lchild;
        else q->lchild = s->lchild;
        delete s;
    }
}

Status DeleteBST(BiTree &T,KeyType key) {
    // ������������T�д��ڹؼ��ֵ���key������Ԫ��ʱ����ɾ��������Ԫ�ؽ�㣬
    // ������TRUE�����򷵻�FALSE���㷨9.7
    if (!T) return FALSE;
    else {
        if (EQ(key, T->data.key)) Delete(T);
        else if (LT(key, T->data.key)) return DeleteBST(T->lchild, key);
        else return DeleteBST(T->rchild, key);
    }
}

void TraverseDSTable(BiTree DT,void(*Visit)(ElemType)) {
    // ��ʼ����: ��̬���ұ�DT���ڣ�Visit�ǶԽ�������Ӧ�ú���
    // �������: ���ؼ��ֵ�˳���DT��ÿ�������ú���Visit()һ��������һ��
    if(DT)
    {
        TraverseDSTable(DT->lchild,Visit); // ���������������
        Visit(DT->data); // �ٷ��ʸ����
        TraverseDSTable(DT->rchild,Visit); // ����������������
    }
}