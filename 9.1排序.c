给定N个（长整型范围内的）整数，要求输出从小到大排序后的结果。

本题旨在测试各种不同的排序算法在各种数据情况下的表现。各组测试数据特点如下：

数据1：只有1个元素；
数据2：11个不相同的整数，测试基本正确性；
数据3：103个随机整数；
数据4：104个随机整数；
数据5：105个随机整数；
数据6：105个顺序整数；
数据7：105个逆序整数；
数据8：105个基本有序的整数；
数据9：105个随机正整数，每个数字不超过1000。
## 输入格式:
输入第一行给出正整数N（≤10^5），随后一行给出N个（长整型范围内的）整数，其间以空格分隔。

## 输出格式:
在一行中输出从小到大排序后的结果，数字间以1个空格分隔，行末不得有多余空格。

## 输入样例:
```
11
4 981 10 -17 0 -20 29 50 8 43 -5
```
## 输出样例:
>-20 -17 -5 0 4 8 10 29 43 50 981

code：
```c
#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

void Bubble_Sort(int A[], int N);
void Insert_Sort(int A[], int N);
void Shell_Sort(int A[], int N);
void Heap_Sort(int A[], int N);
void Merge_Sort(int A[], int N);
void PrintA(int A[], int N);
void Swap(int* a, int*b);
void PercDown(int A[], int p, int N);
void Merge(int A[], int TmpA[], int L, int R, int RightEnd);
void Msort(int A[], int TmpA[], int L, int RightEnd);

int main(){
	int N;
	scanf("%d", &N);
	int *A = (int*)malloc(sizeof(int)*N);
	int i;
	for (i = 0; i < N; i++)
		scanf("%d", &A[i]);
	//Bubble_Sort(A, N);
	//Insert_Sort(A, N);
	//Shell_Sort(A, N);
	//Heap_Sort(A, N);
	//Merge_Sort(A, N);
	PrintA(A, N);
	return 0;
}

void Swap(int* a, int*b){
	int t = *a; *a = *b; *b = t;
}

void PrintA(int A[], int N){
	int i;
	for (i = 0; i < N; i++){
		printf("%d", A[i]);
		if (i == N - 1) printf("\n");
		else printf(" ");
	}	
}

void Bubble_Sort(int A[], int N){
	int P,i;
	int flag = 0;
	for (P = N - 1; P >= 0; P--){
		for (i = 0; i < P; i++){
			if (A[i]>A[i + 1]){
				Swap(&A[i], &A[i + 1]);
				flag = 1;
			}
		}
		if (flag == 0) break;
	}
}

void Insert_Sort(int A[], int N){
	int P, temp,i;
	for (P = 1; P < N; P++){
		temp = A[P];
		for (i = P; i>0 && A[i - 1] > temp; i--)
			A[i] = A[i - 1];
		A[i] = temp;
	}
}

void Shell_Sort(int A[], int N){ 
	// 希尔排序 - 用Sedgewick增量序列
	int Si, D, P, i;
	int Tmp;
	//列出一小部分增量 
	int Sedgewick[] = { 929, 505, 209, 109, 41, 19, 5, 1, 0 };

	for (Si = 0; Sedgewick[Si] >= N; Si++);
    // 初始的增量Sedgewick[Si]不能超过待排序列长度

	for (D = Sedgewick[Si]; D>0; D = Sedgewick[++Si])
	for (P = D; P<N; P++) { //插入排序
		Tmp = A[P];
		for (i = P; i >= D && A[i - D]>Tmp; i -= D)
			A[i] = A[i - D];
		A[i] = Tmp;
	}
}

void PercDown(int A[], int p, int N){ 
	// 将N个元素的数组中以A[p]为根的子堆调整为最大堆 
	int Parent, Child;
	int X;
	X = A[p]; // 取出根结点存放的值 
	for (Parent = p; (Parent * 2 + 1)<N; Parent = Child) {
		Child = Parent * 2 + 1;
		if ((Child != N - 1) && (A[Child]<A[Child + 1]))
			Child++;  /* Child指向左右子结点的较大者 */
		if (X >= A[Child]) break; /* 找到了合适位置 */
		else  /* 下滤X */
			A[Parent] = A[Child];
	}
	A[Parent] = X;
}

void Heap_Sort(int A[], int N){ 
	int i;
	for (i = N / 2 - 1; i >= 0; i--)// 建立最大堆 
		PercDown(A, i, N);
	for (i = N - 1; i>0; i--) {// 删除最大堆顶 
		Swap(&A[0], &A[i]); 
		PercDown(A, 0, i);
	}
}

/*归并排序 - 递归实现
L = 左边起始位置, R = 右边起始位置, RightEnd = 右边终点位置*/
void Merge(int A[], int TmpA[], int L, int R, int RightEnd){ 
	// 将有序的A[L]~A[R-1]和A[R]~A[RightEnd]归并成一个有序序列
	int LeftEnd, NumElements, Tmp;
	int i;

	LeftEnd = R - 1; // 左边终点位置 
	Tmp = L;         //有序序列的起始位置 
	NumElements = RightEnd - L + 1;

	while (L <= LeftEnd && R <= RightEnd) {
		if (A[L] <= A[R])
			TmpA[Tmp++] = A[L++]; // 将左边元素复制到TmpA 
		else
			TmpA[Tmp++] = A[R++]; // 将右边元素复制到TmpA 
	}
	while (L <= LeftEnd)
		TmpA[Tmp++] = A[L++]; // 直接复制左边剩下的
	while (R <= RightEnd)
		TmpA[Tmp++] = A[R++]; //直接复制右边剩下的

	for (i = 0; i < NumElements; i++, RightEnd--)
		A[RightEnd] = TmpA[RightEnd]; // 将有序的TmpA[]复制回A[]
}
void Msort(int A[], int TmpA[], int L, int RightEnd){ 
	int Center;
	if (L < RightEnd) {
		Center = (L + RightEnd) / 2;
		Msort(A, TmpA, L, Center);              // 递归解决左边 
		Msort(A, TmpA, Center + 1, RightEnd);     //递归解决右边 
		Merge(A, TmpA, L, Center + 1, RightEnd);  // 合并两段有序序列
	}
}
void Merge_Sort(int A[], int N){ 
	int *TmpA;
	TmpA = (int *)malloc(N*sizeof(int));
	Msort(A, TmpA, 0, N - 1);
	free(TmpA);
} 
```
