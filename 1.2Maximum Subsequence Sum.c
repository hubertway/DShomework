Given a sequence of K integers{N1 , N2 , ..., NK}.A continuous subsequence is defined to be{Ni, Ni+1, ..., Nj }.where 1≤i≤j≤K. 
The Maximum Subsequence is the continuous subsequence which has the largest sum of its elements. 
For example, given sequence { -2, 11, -4, 13, -5, -2 }, its maximum subsequence is { 11, -4, 13 } with the largest sum being 20.

Now you are supposed to find the largest sum, together with the first and the last numbers of the maximum subsequence.

Input Specification:
Each input file contains one test case. Each case occupies two lines. The first line contains a positive integer K (≤10000). The second line contains K numbers, separated by a space.

Output Specification:
For each test case, output in one line the largest sum, together with the first and the last numbers of the maximum subsequence. The numbers must be separated by one space, but there must be no extra space at the end of a line. In case that the maximum subsequence is not unique, output the one with the smallest indices i and j (as shown by the sample case). If all the K numbers are negative, then its maximum sum is defined to be 0, and you are supposed to output the first and the last numbers of the whole sequence.

Sample Input:
10
-10 1 2 3 4 -5 -23 3 7 -21
Sample Output:
10 1 4

#include <stdio.h>
#include <stdlib.h>
 
int MaxSubseqSum( int A[] , int N , int* first , int* last); 
 
int main(){
 	int K;
 	scanf("%d",&K);
 	int *A;
 	A = (int*)malloc( K*sizeof(int));
 	int i;
 	int flag = 0;
 	for( i = 0; i < K; i++){
 		scanf("%d",&A[i]);
 		if(A[i] >= 0){
 			flag = 1;
		 }
	 }
	int sum = 0;
	if(flag){
	int first,last;
	first = last = 0;
	sum = MaxSubseqSum( A , K , &first , &last);
	printf("%d %d %d", sum , A[first] , A[last]);
	}else{
	printf("%d %d %d", sum , A[0] , A[K-1]);	
	}
	free(A);
 	return 0;
}
 
int MaxSubseqSum( int A[] , int N , int* first , int* last){
 	int ThisSum, MaxSum;
 	ThisSum = 0;
 	MaxSum = -1;
 	int i;
 	int t = 0;
 	for( i = 0; i < N ; i++){
 		ThisSum += A[i];
 		if(ThisSum > MaxSum){
 			MaxSum = ThisSum;
 			*first = t;
 			*last = i;
		}else if(ThisSum < 0){
		 	ThisSum = 0;
			if( A[i+1] >= 0 && i < N)	{
				t = i+1;	 
			}
		}
	 }
	 return MaxSum; 
}
