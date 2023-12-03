#include"public1.H"
#include"p8.h"

void InsertSort(SqList &L) {
    // 对顺序表L作直接插入排序。
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
    // 对顺序表L作折半插入排序。
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
    // 对顺序表L作一趟希尔插入排序。本算法是和一趟直接插入排序相比，
    // 作了以下修改：
    // 1.前后记录位置的增量是dk,而不是1;
    // 2.r[0]只是暂存单元,不是哨兵。当j<=0时,插入位置已找到。
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
    // 按增量序列dlta[0..t-1]对顺序表L作希尔排序。
    int k;
    for(k=0;k<t;++k)
    {
        ShellInsert(L,dlta[k]); // 一趟增量为dlta[k]的插入排序
    }
}

void bubble_sort(SqList &L) {
    // 起泡排序
    // 每次冒上一个最大值
    // 在倒数第二个最大值到位后 最后一个默认就是第一个
    // 因此外层循环可以少一次
    for (int i = 1; i < L.length; i++) {
        // 对比
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
    // 交换顺序表L中子表L.r[low..high]的记录，使枢轴记录到位，
    // 并返回其所在位置，此时在它之前(后)的记录均不大(小)于它。
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

//快速排序的函数
void QSort(SqList &L,int low,int high) {
    // 对顺序表L中的子序列L.r[low..high]作快速排序。
    if (low < high) {
        int pivotloc = Partition(L, low, high);
        QSort(L, low, pivotloc - 1);
        QSort(L, pivotloc + 1, high);
    }
}

void QuickSort(SqList &L) {
    // 对顺序表L作快速排序。
    QSort(L,1,L.length);

}

int SelectMinKey(SqList L,int i) {
    // 返回在L.r[i..L.length]中key最小的记录的序号
    int minIndex = i;
    for (int j = i + 1; j <= L.length; j++) {
        if (L.r[j].key < L.r[minIndex].key) {
            minIndex = j;
        }
    }
    return minIndex;
}

//选择排序
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

//堆排序
void HeapAdjust(SqList &H,int s,int m) {
    // 已知H.r[s..m]中记录的关键字除H.r[s].key之外均满足堆的定义，本函数
    // 调整H.r[s]的关键字,使H.r[s..m]成为一个大顶堆(对其中记录的关键字而言)
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
    // 对顺序表H进行堆排序。
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
    for(i=0;i<N;i++) // 给l1.r赋值
      l1.r[i+1]=d[i];
    l1.length=N;

    l7=l6=l5=l4=l3=l2=l1; // 复制顺序表l2、l3与l1相同
    printf("排序前:\n");
    print(l1);

    InsertSort(l1);
    printf("直接插入排序后:\n");
    print(l1);

    BInsertSort(l2);
    printf("折半插入排序后:\n");
    print(l2);

    int dt[3]={5,3,1}; // 增量序列数组
    ShellInsertSort(l3,dt,3);
    printf("希尔排序后:\n");
    print(l3);

    bubble_sort(l4);
    printf("起泡排序后:\n");
    print(l4);

    QuickSort(l5);
    printf("快速排序后:\n");
    print(l5);

    SelectSort(l6);
    printf("选择排序后:\n");
    print(l6);

    HeapSort(l7);
    printf("堆排序后:\n");
    print(l7);

    return 1;
}
