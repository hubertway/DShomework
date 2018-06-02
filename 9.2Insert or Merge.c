According to Wikipedia:

Insertion sort iterates, consuming one input element each repetition, and growing a sorted output list. 
Each iteration, insertion sort removes one element from the input data, finds the location it belongs within the sorted list, and inserts it there. 
It repeats until no input elements remain.

Merge sort works as follows: Divide the unsorted list into N sublists, each containing 1 element (a list of 1 element is considered sorted).
Then repeatedly merge two adjacent sublists to produce new sorted sublists until there is only 1 sublist remaining.

Now given the initial sequence of integers, together with a sequence which is a result of several iterations of some sorting method, can you tell which sorting method we are using?

Input Specification:
Each input file contains one test case. For each case, the first line gives a positive integer N (≤100). Then in the next line, N integers are given as the initial sequence. 
The last line contains the partially sorted sequence of the N numbers. It is assumed that the target sequence is always ascending.
All the numbers in a line are separated by a space.

Output Specification:
For each test case, print in the first line either "Insertion Sort" or "Merge Sort" to indicate the method used to obtain the partial result. 
Then run this method for one more iteration and output in the second line the resuling sequence. It is guaranteed that the answer is unique for each test case. 
All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line.

Sample Input 1:
10
3 1 2 8 7 5 9 4 6 0
1 2 3 7 8 5 9 4 6 0
Sample Output 1:
Insertion Sort
1 2 3 5 7 8 9 4 6 0
Sample Input 2:
10
3 1 2 8 7 5 9 4 0 6
1 3 2 8 5 7 4 9 0 6
Sample Output 2:
Merge Sort
1 2 3 8 4 5 7 9 0 6

code：

#include<stdio.h>
#include<stdlib.h>

void PrintA(int A[], int N);
int IsInsert(int A[],int R[], int N);
void InsertOne(int A[], int N,int B); //插入排序再迭代一次，B为中间序列顺序不对的跳出点
void MergeOne(int A[], int N); //归并排序再迭代一次
void Merge(int A[], int TmpA[], int L, int R, int RightEnd);
void Merge_pass(int A[], int TmpA[], int N, int length);

int main(){
	int N;
	scanf("%d", &N);
	int *A = (int*)malloc(sizeof(int)*N);//原来序列
	int i;
	for (i = 0; i < N; i++)
		scanf("%d", &A[i]);
	int *R = (int*)malloc(sizeof(int)*N);//中间序列
	for (i = 0; i < N; i++)
		scanf("%d", &R[i]);

	int flag = IsInsert(A, R, N);
	if (flag){
		printf("Insertion Sort\n");
		InsertOne(R, N, flag);
		PrintA(R, N);
	}
	else{
		printf("Merge Sort\n");
		MergeOne(R, N);
		PrintA(R, N);
	}
	return 0;
}

void PrintA(int A[], int N){
	int i;
	for (i = 0; i < N; i++){
		printf("%d", A[i]);
		if (i == N - 1) printf("\n");
		else printf(" ");
	}	
}

int IsInsert(int A[], int R[], int N){
	int i,temp;
	for (i = 0; i < N; i++){
		if (R[i] > R[i + 1]){ //判断顺序 
			temp = i;
			break;
		}
	}
	for (++i; i < N; i++){
		if (A[i] != R[i]){ //与原始数列对比
			return 0;
			break;
		}
	}
	if (i == N) return temp+1;
}
void InsertOne(int A[], int N, int B) {
	int  temp, i;
	temp = A[B];
	for (i = B; i>0 && A[i - 1] > temp; i--)
		A[i] = A[i - 1];
	A[i] = temp;
}
void MergeOne(int A[], int N){
	int length ;//归并段长度
	for (length = 2; length < N; length *= 2){
		int temp = length;
		int flag = 0;
		while (temp<=N){
			if (A[temp - 1] <= A[temp])
				temp *= 3;
			else { 
				flag = 1; 
				break;
			}
		}
		if (flag == 1) break;
	}
	int *TmpA = (int *)malloc(sizeof(int)*N);
	Merge_pass(A, TmpA, N, length);//以当前length再归并一次
	free(TmpA);
}

void Merge(int A[], int TmpA[], int L, int R, int RightEnd){ 
	int LeftEnd, NumElements, Tmp;
	int i;

	LeftEnd = R - 1; // 左边终点位置 
	Tmp = L;      //有序序列的起始位置 
	NumElements = RightEnd - L + 1;

	while (L <= LeftEnd && R <= RightEnd) {
		if (A[L] <= A[R])
			TmpA[Tmp++] = A[L++]; // 将左边元素复制到TmpA 
		else
			TmpA[Tmp++] = A[R++]; // 将右边元素复制到TmpA 
	}

	while (L <= LeftEnd) // 直接复制左边剩下的
		TmpA[Tmp++] = A[L++]; 
	while (R <= RightEnd)//直接复制右边剩下的
		TmpA[Tmp++] = A[R++]; 

	for (i = 0; i < NumElements; i++, RightEnd--)
		A[RightEnd] = TmpA[RightEnd]; // 将有序的TmpA[]复制回A[] 
}
void Merge_pass(int A[], int TmpA[], int N, int length){
	int i, j;
	for (i = 0; i <= N - 2 * length; i += 2 * length)
		Merge(A, TmpA, i, i + length, i + 2 * length - 1);
	if (i + length < N) 
		Merge(A, TmpA, i, i + length, N - 1);
	else
	for (j = i; j < N; j++) TmpA[j] = A[j];
}
