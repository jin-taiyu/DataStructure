 #define NULLKEY 0 // 0为无记录标志
 #define N 10 // 数据元素个数
 typedef int KeyType; // 设关键字域为整型
 struct ElemType // 数据元素类型
 {
   KeyType key;
   int ord;
 };
 //开放定址哈希表的存储结构
 int hashsize[]={11,19,29,37}; // 哈希表容量递增表，一个合适的素数序列
 int m=0; // 哈希表表长，全局变量
 struct HashTable
 {
   ElemType *elem; // 数据元素存储基址，动态分配数组
   int count; // 当前数据元素个数
   int sizeindex; // hashsize[sizeindex]为当前容量
 };

 #define SUCCESS 1
 #define UNSUCCESS 0
 #define DUPLICATE -1
