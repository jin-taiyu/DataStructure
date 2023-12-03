#include"public1.H"
#include"p8.h"

void InsertSort(SqList &L) {
    // ��˳���L��ֱ�Ӳ�������
    int i, j;
    for (i = 2; i <= L.length; i++) {
        if (LT(L.r[i].key, L.r[i - 1].key)) {
            L.r[0] = L.r[i];
            L.r[i] = L.r[i - 1];
            for (j = i - 2; LT(L.r[0].key, L.r[j].key); j--) {
                L.r[j + 1] = L.r[j];
            }
            L.r[j + 1] = L.r[0];
        }
    }
}

void BInsertSort(SqList &L) {
    // ��˳���L���۰��������
    int i, j;
    for (i = 2; i <= L.length; i++) {
        L.r[0] = L.r[i];
        int low = 1;
        int high = i - 1;
        while (low <= high) {
            int m = (low + high) / 2;
            if (LT(L.r[0].key, L.r[m].key)) high = m - 1;
            else low = m + 1;
        }
        for (j = i - 1; j >= high + 1; j--) L.r[j + 1] = L.r[j];
        L.r[high + 1] = L.r[0];
    }
}

void ShellInsert(SqList &L,int dk) {
    // ��˳���L��һ��ϣ���������򡣱��㷨�Ǻ�һ��ֱ�Ӳ���������ȣ�
    // ���������޸ģ�
    // 1.ǰ���¼λ�õ�������dk,������1;
    // 2.r[0]ֻ���ݴ浥Ԫ,�����ڱ�����j<=0ʱ,����λ�����ҵ���
    int i, j;
    for (i = dk + 1; i <= L.length; i++) {
        if (LT(L.r[i].key, L.r[i - dk].key)) {
            L.r[0] = L.r[i];
            for (j = i - dk; j > 0 && LT(L.r[0].key, L.r[j].key); j -= dk) {
                L.r[j + dk] = L.r[j];
            }
            L.r[j + dk] = L.r[0];
        }
    }
}

void ShellInsertSort(SqList &L,int dlta[],int t) {
    // ����������dlta[0..t-1]��˳���L��ϣ������
    int k;
    for(k=0;k<t;++k)
    {
        ShellInsert(L,dlta[k]); // һ������Ϊdlta[k]�Ĳ�������
    }
}

void bubble_sort(SqList &L) {
    // ��������
    // ÿ��ð��һ�����ֵ
    // �ڵ����ڶ������ֵ��λ�� ���һ��Ĭ�Ͼ��ǵ�һ��
    // ������ѭ��������һ��
    for (int i = 1; i < L.length; i++) {
        // �Ա�
        for (int j = 1; j <= L.length - i; j++) {
            if (L.r[j].key > L.r[j + 1].key) {
                RedType tmp = L.r[j];
                L.r[j] = L.r[j + 1];
                L.r[j + 1] = tmp;
            }
        }
    }
}

int Partition(SqList &L,int low,int high) {
    // ����˳���L���ӱ�L.r[low..high]�ļ�¼��ʹ�����¼��λ��
    // ������������λ�ã���ʱ����֮ǰ(��)�ļ�¼������(С)������
    KeyType pivotkey = L.r[low].key;
    while (low < high) {
        RedType tmp;
        while (low < high && L.r[high].key >= pivotkey) --high;
        tmp = L.r[low];
        L.r[low] = L.r[high];
        L.r[high] = tmp;
        while (low < high && L.r[low].key <= pivotkey) ++low;
        tmp = L.r[low];
        L.r[low] = L.r[high];
        L.r[high] = tmp;
    }
    return low;
}

//��������ĺ���
void QSort(SqList &L,int low,int high) {
    // ��˳���L�е�������L.r[low..high]����������
    if (low < high) {
        int pivotloc = Partition(L, low, high);
        QSort(L, low, pivotloc - 1);
        QSort(L, pivotloc + 1, high);
    }
}

void QuickSort(SqList &L) {
    // ��˳���L����������
    QSort(L,1,L.length);

}

int SelectMinKey(SqList L,int i) {
    // ������L.r[i..L.length]��key��С�ļ�¼�����
    int minIndex = i;
    for (int j = i + 1; j <= L.length; j++) {
        if (L.r[j].key < L.r[minIndex].key) {
            minIndex = j;
        }
    }
    return minIndex;
}

//ѡ������
void SelectSort(SqList &L) {
    int i, j;
    for (i = 1; i < L.length; i++) {
        j = SelectMinKey(L, i);
        if (i != j) {
            RedType tmp = L.r[i];
            L.r[i] = L.r[j];
            L.r[j] = tmp;
        }
    }
}

//������
void HeapAdjust(SqList &H,int s,int m) {
    // ��֪H.r[s..m]�м�¼�Ĺؼ��ֳ�H.r[s].key֮�������ѵĶ��壬������
    // ����H.r[s]�Ĺؼ���,ʹH.r[s..m]��Ϊһ���󶥶�(�����м�¼�Ĺؼ��ֶ���)
    int j;
    RedType rc = H.r[s];
    for (j = 2 * s; j <= m; j *= 2) {
        if (j < m && LT(H.r[j].key, H.r[j + 1].key)) ++j;
        if (!LT(rc.key, H.r[j].key)) break;
        H.r[s] = H.r[j];    s = j;
    }
    H.r[s] = rc;
}

void HeapSort(SqList &H) {
    // ��˳���H���ж�����
    int i;
    for (i = H.length / 2; i > 0; --i) {
        HeapAdjust(H, i, H.length);
    }
    for (i = H.length; i > 1; --i) {
        RedType tmp = H.r[1];
        H.r[1] = H.r[i];
        H.r[i] = tmp;

        HeapAdjust(H, 1, i - 1);
    }
}



void print(SqList L) {
   int i;
   for(i=1;i<=L.length;i++)
     printf("(%d,%d)",L.r[i].key,L.r[i].otherinfo);
   printf("\n");
}


int main()
{
    RedType d[N]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
    SqList l1,l2,l3,l4,l5,l6,l7;
    int i;
    for(i=0;i<N;i++) // ��l1.r��ֵ
      l1.r[i+1]=d[i];
    l1.length=N;

    l7=l6=l5=l4=l3=l2=l1; // ����˳���l2��l3��l1��ͬ
    printf("����ǰ:\n");
    print(l1);

    InsertSort(l1);
    printf("ֱ�Ӳ��������:\n");
    print(l1);

    BInsertSort(l2);
    printf("�۰���������:\n");
    print(l2);

    int dt[3]={5,3,1}; // ������������
    ShellInsertSort(l3,dt,3);
    printf("ϣ�������:\n");
    print(l3);

    bubble_sort(l4);
    printf("���������:\n");
    print(l4);

    QuickSort(l5);
    printf("���������:\n");
    print(l5);

    SelectSort(l6);
    printf("ѡ�������:\n");
    print(l6);

    HeapSort(l7);
    printf("�������:\n");
    print(l7);

    return 1;
}