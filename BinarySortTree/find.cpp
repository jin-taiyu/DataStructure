 #include"public1.h"
 #include"BiTree.h"
 #include"BST.h"

 void print(ElemType c)
 {
   printf("(%d,%d) ",c.key,c.others);
 }

 int main()
 {
   BiTree dt,p;
   int i;
   KeyType j;
   ElemType r[N]={{45,1},{12,2},{53,3},{3,4},{37,5},{24,6},{100,7},{61,8},{90,9},{78,10}};
   InitDSTable(dt); // 构造空表
   for(i=0;i<N;i++)
     InsertBST(dt,r[i]); // 依次插入数据元素
   TraverseDSTable(dt,print);
   printf("\n请输入待查找的值: ");
   scanf("%d",&j);
   p=SearchBST(dt,j);
   if(p)
   {
     printf("表中存在此值。");
     //选做：删除该找到的结点，并遍历二叉排序树，查看删除后的结果
     printf("\n");
   }
   else
     printf("表中不存在此值\n");

    /*
    实验二叉排序树的删除算法
    */

    // 如果查找到了便启动删除
    KeyType toDelete;
    // 题目要求使用之前查找的值
    toDelete = j;
    DeleteBST(dt, toDelete);
    cout << "删除此值后：" << endl;
    TraverseDSTable(dt, print);


    // 查找第k个最小的元素
    int kth;
    int ans;
    cout << endl;
    priority_queue<int, vector<int>, greater<int>> minHeap;
    cout << "请输入要查找的第k个最小的元素" << endl;
    cin >> kth;
    ans = kthSmallest(dt, kth, minHeap);
    if (ans != -1) {
        cout << "第" << kth << "个最小的元素是" << ans << endl;
    }
    else {
        cout << "输入的k超出范围" << endl;
    }
   DestroyDSTable(dt);
   return 1;
 }
