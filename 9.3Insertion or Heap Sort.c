According to Wikipedia:

Insertion sort iterates, consuming one input element each repetition, and growing a sorted output list. 
Each iteration, insertion sort removes one element from the input data, finds the location it belongs within the sorted list, and inserts it there.
It repeats until no input elements remain.

Heap sort divides its input into a sorted and an unsorted region, and it iteratively shrinks the unsorted region by extracting the largest element and moving that to the sorted region.
it involves the use of a heap data structure rather than a linear-time search to find the maximum.

Now given the initial sequence of integers, together with a sequence which is a result of several iterations of some sorting method, can you tell which sorting method we are using?

Input Specification:
Each input file contains one test case. For each case, the first line gives a positive integer N (≤100). 
Then in the next line, N integers are given as the initial sequence. The last line contains the partially sorted sequence of the N numbers. It is assumed that the target sequence is always ascending. 
All the numbers in a line are separated by a space.

Output Specification:
For each test case, print in the first line either "Insertion Sort" or "Heap Sort" to indicate the method used to obtain the partial result.
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
3 1 2 8 7 5 9 4 6 0
6 4 5 1 0 3 2 7 8 9
Sample Output 2:
Heap Sort
5 4 3 1 0 2 6 7 8 9

code：
#include<stdio.h>
#include<stdlib.h>

void PrintA(int A[], int N);
int IsInsert(int A[],int R[], int N);
void InsertOne(int A[], int N,int B); 
void Swap(int *a, int *b);
void PercDown(int A[], int p, int N);
void HeapSortOne(int R[], int N);

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
		printf("Heap Sort\n");
		HeapSortOne(R,  N);
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
void Swap(int *a, int *b){
	int t = *a; *a = *b; *b = t;
}
void PercDown(int A[], int p, int N){ 
	int Parent, Child;
	int X;
	X = A[p]; 
	for (Parent = p; (Parent * 2+1 )<N; Parent = Child) {
		Child = Parent * 2 + 1;
		if ((Child != N - 1) && (A[Child]<A[Child + 1]))
			Child++;  
		if (X >= A[Child]) break; 
		else  A[Parent] = A[Child];
	}
	A[Parent] = X;
}
void HeapSortOne( int R[], int N){
	int i = N-1;
	while (i>0 && R[i] >= R[i - 1]) i--;
	Swap(&R[0], &R[i]);
	PercDown(R, 0, i);
}
