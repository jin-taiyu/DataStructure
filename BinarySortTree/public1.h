 #include<string.h>
 #include<ctype.h>
 #include<malloc.h> // malloc()等
 #include<limits.h> // INT_MAX等
 #include<stdio.h> // EOF(=^Z或F6),NULL
 #include<stdlib.h> // atoi()
 #include<io.h> // eof()
 #include<math.h> // floor(),ceil(),abs()
 #include<process.h> // exit()
 #include<iostream>
 using namespace std;
 // 函数结果状态代码
 #define TRUE 1
 #define FALSE 0
 #define OK 1
 #define ERROR 0
 #define INFEASIBLE -1
 //Status 是函数的类型，其值是函数结果状态代码，如OK等
 typedef int Status;
 //对两个数值型关键字的比较约定为如下的宏定义
 #define EQ(a,b) ((a)==(b))
 #define LT(a,b) ((a)<(b))
 #define LQ(a,b) ((a)<=(b))



