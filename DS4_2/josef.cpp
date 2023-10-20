#include "LinkQueue.h"

int flag[30] = {0};
int num = 30;

void AllEnQueue(LinkQueue &Q) {
    for (int i = 0; i < 30; i++) {
            if (!flag[i]) {
                EnQueue(Q, i);
            }
    }
}

int main()
{
    cout << "被扔下大海的位置依次为:" << endl;
    // 定义变量
    LinkQueue ranks;
    InitQueue(ranks);

    while (num >15) {
        QElemType temp;
        // 开始报数
        for (int i = 0; i < 9; i++) {
            // 若队空则补充
            //顺便给出队做保护
            if (QueueEmpty(ranks)) {
                AllEnQueue(ranks);
            }
            DeQueue(ranks, temp);
        }
        num--; // 丢掉一个
        flag[temp] = 1;
        cout << temp + 1 << "    ";
    }
    // 销毁队列
    DestroyQueue(ranks);
	return 1;
}
