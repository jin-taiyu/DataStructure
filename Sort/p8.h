 typedef int InfoType; 
 #define N 8 
 #define MAXSIZE 20 // 一个用作示例的小顺序表的最大长度
 typedef int KeyType; // 定义关键字类型为整型
 struct RedType // 记录类型
 {
   KeyType key; // 关键字项
   InfoType otherinfo; // 其它数据项，具体类型在主程中定义
 };

 struct SqList // 顺序表类型
 {
   RedType r[MAXSIZE+1]; // r[0]闲置或用作哨兵单元
   int length; // 顺序表长度
 };
