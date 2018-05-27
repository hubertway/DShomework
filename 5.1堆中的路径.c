将一系列给定数字插入一个初始为空的小顶堆H[]。随后对任意给定的下标i，打印从H[i]到根结点的路径。

输入格式:
每组测试第1行包含2个正整数N和M(≤1000)，分别是插入元素的个数、以及需要打印的路径条数。下一行给出区间[-10000, 10000]内的N个要被插入一个初始为空的小顶堆的整数。最后一行给出M个下标。
输出格式:
对输入中给出的每个下标i，在一行中输出从H[i]到根结点的路径上的数据。数字间以1个空格分隔，行末不得有多余空格。

输入样例:
5 3
46 23 26 24 10
5 4 3
输出样例:
24 23 10
46 23 10
26 10

code:
#include <stdio.h>
#include <stdlib.h>

#define MINDATA -10001
 typedef struct HNode{
	int *Data; 		  // 存储元素的数组 
	int Size;         // 堆中当前元素个数 
	int Capacity;     //堆的最大容量 
 }*Heap;
typedef Heap MinHeap; //最小堆 

MinHeap CreateHeap(int MaxSize);//建堆
void BuildHeap(MinHeap H);//调整H->Data[]中的元素，使满足最小堆的有序性
void PercDown(MinHeap H, int p);//下滤：将H中以H->Data[p]为根的子堆调整为最小堆
void OutWay(MinHeap H, int i);//输出路径元素

int main()
{
	int N, M;
	scanf("%d %d", &N, &M);
	MinHeap H = CreateHeap(N);
	int i;
	for (i = 1; i < N + 1; i++){//先讲读入元素放进堆中
		scanf("%d", &H->Data[i]);
		H->Size++;
	}
	BuildHeap(H);
	int j;
	int index;
	for (j = 0; j < M; j++){
		scanf("%d", &index);
		OutWay(H, index);
	}
	return 0;
}

MinHeap CreateHeap(int MaxSize){
	MinHeap H = (MinHeap)malloc(sizeof(struct HNode));
	H->Data = (int *)malloc((MaxSize + 1)*sizeof(int));
	H->Size = 0;
	H->Capacity = MaxSize;
	H->Data[0] = MINDATA;
	return H;
}
void BuildHeap(MinHeap H){
	int i;
	for (i = H->Size / 2; i > 0; i--){
		PercDown(H, i);
	}
}
void PercDown(MinHeap H, int p){
	int Parent, Child;
	int X;
	X = H->Data[p]; /* 取出根结点存放的值 */
	for (Parent = p; Parent * 2 <= H->Size; Parent = Child) {
		Child = Parent * 2;
		if ((Child != H->Size) && (H->Data[Child]>H->Data[Child + 1]))
			Child++;  /* Child指向左右子结点的较小者 */
		if (X <= H->Data[Child]) break; /* 找到了合适位置 */
		else  /* 下滤X */
			H->Data[Parent] = H->Data[Child];
	}
	H->Data[Parent] = X;
}
void OutWay(MinHeap H, int i){
	while (i>0 && i < H->Size){
		printf("%d ", H->Data[i]);
		if (i > 1) printf(" ");
		else printf("\n");
		i /= 2;
	}
}

//老师答案讲解，边插入边排序，最终顺序和自己做的叶节点顺序不同
#include <stdio.h>
#define MaxN 1001
#define MinH -10001

int H[MaxN],size;
void Creat(){
    size = 0;
    H[0] = MinH;
} 
void Insert(int X){
    int i;
    for(i = ++size; H[i/2] > X; i/=2) 
        H[i] = H[i/2];
    H[i] = X;
}
int main()
{
    int N,M,x;
    scanf("%d %d", &N, &M);
    Creat();
    int i; 
    for(i = 0; i < N; i++) {
        scanf("%d",&x);
        Insert(x);
    }
    int j;
    for(i = 0; i < M; i++) {
        scanf("%d",&j);
        while(j > 0) {
            printf("%d",H[j]);
            if (j > 1) printf(" ");
			else printf("\n");
			j /= 2;
        }
    }
    return 0;
}
