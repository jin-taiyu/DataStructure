 typedef int InfoType; 
 #define N 8 
 #define MAXSIZE 20 // һ������ʾ����С˳�������󳤶�
 typedef int KeyType; // ����ؼ�������Ϊ����
 struct RedType // ��¼����
 {
   KeyType key; // �ؼ�����
   InfoType otherinfo; // ������������������������ж���
 };

 struct SqList // ˳�������
 {
   RedType r[MAXSIZE+1]; // r[0]���û������ڱ���Ԫ
   int length; // ˳�������
 };