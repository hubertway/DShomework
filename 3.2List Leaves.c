Given a tree, you are supposed to list all the leaves in the order of top down, and left to right.

Input Specification:
Each input file contains one test case. For each case, the first line gives a positive integer N (≤10) which is the total number of nodes in the tree -- and hence the nodes are numbered from 0 to N−1. Then N lines follow, each corresponds to a node, and gives the indices of the left and right children of the node. 
If the child does not exist, a "-" will be put at the position. Any pair of children are separated by a space.
Output Specification:
For each test case, print in one line all the leaves' indices in the order of top down, and left to right.
There must be exactly one space between any adjacent numbers, and no extra space at the end of the line.

Sample Input:
8
1 -
- -
0 -
2 7
- -
- -
5 -
4 6
Sample Output:
4 1 5



/*题意：
给出一个树，从上到下从左到右将它的叶节点列出。（层序遍历）
输入格式：
第一行 给出一个<=10的整数N作为树的结点个数。
结点用 0 到 N-1 编号 ，以此给出N行，并给出左右孩子结点的编号，
如果孩子节点为空，用 “ - ” 表示.给出的每对数据用空格隔开。
输出格式：
在一行中从上到下从左到右将所有叶节点按顺序打印。相邻数字间有空格，结尾无空格。
*/

code:

#include <stdio.h>
#include <stdlib.h>

#define MaxTree 10
#define Null -1
#define Tree int
typedef struct Tnode{ //树结构 
	int data;
	Tree left;
	Tree right; 
} BinTree;

typedef struct TLevelQueue{ //为了层序遍历创建队列结构 
	int *data;
	int front, rear; //队列的头、尾指针 
	int MaxSize; //队列最大容量
}*PQueue;
typedef PQueue Queue;

Tree Build(BinTree T[]);
void Leaves(Tree R, BinTree T[]);
Queue CreateQueue( int MaxSize );
int IsEmpty( Queue Q );//队列判空 
void AddQ( Queue Q, int x );//入队 
int DeleteQ( Queue Q );//出队 

int main(){
	Tree R; 
	BinTree T[MaxTree];
	R = Build(T);	
	Leaves(R ,T);
	return 0;
}

Tree Build(BinTree T[]){
	int num;
	int root = Null;
	scanf("%d", &num);
	if (num){
		int i;
		char cl, cr;
		int *check = (int*)malloc(sizeof(int)*num);//为了查找根节点建立check数组
		for (i = 0; i < num; i++) check[i] = 0;
		for (i = 0; i < num ; i++){
			T[i].data = i ; 
			scanf("\n%c %c",&cl,&cr);//方便处理'-'输入 
			if (cl != '-'){
				T[i].left = cl - '0';
				check[T[i].left] = 1;
			}else T[i].left = Null;
			if (cr != '-'){
				T[i].right = cr - '0';
				check[T[i].right] = 1;
			}else T[i].right = Null;
		}
		for (i = 0; i < num; i++){
			if (!check[i]) break;//为零的即没有其他节点指向它，故为根节点
		}
		root = i;
	}
	return root;
}
void Leaves(Tree R, BinTree T[]){
    if ( R != Null) {
    	int temp;
    	Queue Q; 
    	Q = CreateQueue(MaxTree);
    	AddQ( Q, T[R].data );
    	while(!IsEmpty( Q )){
    		temp = DeleteQ( Q );
    		if ( T[temp].left!= Null)  AddQ( Q, T[temp].left); 
			if ( T[temp].right!= Null)  AddQ( Q, T[temp].right);
			if ( T[temp].left == Null && T[temp].right == Null) {
				printf("%d", temp);
				if(!IsEmpty( Q ))printf(" ");
				else printf("\n");
			}
		}
	}
}
Queue CreateQueue(int MaxSize)
{
    Queue Q = (Queue)malloc(sizeof(struct TLevelQueue));
    Q->data = (int *)malloc(MaxSize * sizeof(int));
    Q->front = Q->rear = 0;
    Q->MaxSize = MaxSize;
    return Q;
}
int IsEmpty( Queue Q ){
	if (Q->front == Q->rear) return 1;
	else return 0;

}
void AddQ( Queue Q, int x ){
	Q->rear = (Q->rear+1) % (Q->MaxSize);
    Q->data[Q->rear] = x;
}
int DeleteQ( Queue Q ){
	int temp;
	Q->front =(Q->front+1)%(Q->MaxSize);
    temp = Q->data[Q->front]; 
    return temp;
}
