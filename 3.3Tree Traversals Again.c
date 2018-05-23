An inorder binary tree traversal can be implemented in a non-recursive way with a stack. 
For example, suppose that when a 6-node binary tree (with the keys numbered from 1 to 6) is traversed, the stack operations are:
push(1); push(2); push(3); pop(); pop(); push(4); pop(); pop(); push(5); push(6); pop(); pop(). 
Then a unique binary tree can be generated from this sequence of operations. 
Your task is to give the postorder traversal sequence of this tree.

Input Specification:
Each input file contains one test case. For each case, the first line contains a positive integer N (≤30) which is the total number of nodes in a tree (and hence the nodes are numbered from 1 to N).
Then 2N lines follow, each describes a stack operation in the format:
"Push X" where X is the index of the node being pushed onto the stack; or "Pop" meaning to pop one node from the stack.
Output Specification:
For each test case, print the postorder traversal sequence of the corresponding tree in one line. A solution is guaranteed to exist.
All the numbers must be separated by exactly one space, and there must be no extra space at the end of the line.

Sample Input:
6
Push 1
Push 2
Push 3
Pop
Pop
Push 4
Pop
Pop
Push 5
Push 6
Pop
Pop
Sample Output:
3 4 2 6 5 1

/*题意：
已知二叉树中序遍历可以用堆栈非递归实现，尝试后序遍历的堆栈实现。
输入格式：
第一行 给出 <=30 的整数 N 作为树中结点的总个数（用1到N来编号）。
随后给出 2N 行，每行一个堆栈操作，如“Push X”即将X入栈，“Pop”即从堆栈中弹出一个结点。
输出格式:
在一行中打印该树的后序遍历结果。相邻数字间有空格，结尾无空格。
*/
/*分析：
Push顺序为先序遍历
Pop顺序给出中序遍历（即提干中的堆栈实现的具体方式）
故题目实质上是通过 先序 和 中序 来求 后序 ，用递归分而治之。
*/

code:

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Snode{//堆栈结构
	int data;
	struct Snode * next;
}*Prt;
typedef Prt Stack;

Stack Createstack();//建立堆栈
int IsEmpty(Stack S);//判空
void Push(Stack S, int X);//入栈
int Pop(Stack S);//出栈

void Solve(int pre[], int preF, int in[], int inF, int post[], int postF, int N);
void PrintA(int A[],int N );

int main(){
	int N;
	scanf("%d\n", &N);
	char* push = "Push";
	char* pop = "Pop";
	int* pre = (int*)malloc(sizeof(int)*N);
	int* in = (int*)malloc(sizeof(int)*N);
	int* post = (int*)malloc(sizeof(int)*N);
	Stack S = Createstack();
	int i, j;
	int a, b;
	a = 0;
	b = 0;
	for (i = 0; i < 2 * N ; i++){
		char str[5];
		for (j = 0;; j++){
			str[j] = getchar();
			if (str[j] == ' '|| str[j] == '\n') break;//读到空格或回车时，字符串结束
		}str[j] = '\0';
		int x;
		if (!strcmp(str, push)){
			scanf("%d\n", &x);//填写先序数组
			pre[a] = x;
			Push(S, x);
			a++;
		}
		if (!strcmp(str, pop)){
			in[b] = Pop(S);//填写中序数组
			b++;
		}
	}
	Solve(pre, 0, in, 0, post, 0, N);
	PrintA(post, N);
	return 0;
}

void Solve(int pre[], int preF, int in[], int inF, int post[], int postF, int N){
	if (N == 0) return;
	if (N == 1){
		post[postF] = pre[preF];
		return;
	}
	int root = pre[preF];
	post[postF + N - 1] = root;
	int i;
	for (i = 0; i < N;i++){
		if (in[inF + i] == root)
			break;
	}
	int L = i;
	int R = N - L - 1;
	Solve(pre, preF + 1, in, inF, post, postF, L);
	Solve(pre, preF + L + 1, in, inF + L + 1, post, postF + L, R);
}

void PrintA(int A[], int N) {
	int i;
	for (i = 0; i < N; i++){
		printf("%d", A[i]);
		if (i < N - 1) printf(" ");
		else printf("\n");
	}
}

Stack Createstack(){
	Stack S;
	S = (Stack)malloc(sizeof(struct Snode));
	S->next = NULL;
	return S;
}
int IsEmpty(Stack S){
	if (S->next == NULL) return 1;
	else return 0;
}
void Push(Stack S, int X){
	Prt TmpC = (Prt)malloc(sizeof(struct Snode));
	TmpC->data = X;
	TmpC->next = S->next;
	S->next = TmpC;
}
int  Pop(Stack S){
	Prt FstC;
	int  data;
	if (IsEmpty(S) == 0){
		data = S->next->data;
		FstC = S->next;
		S->next = FstC->next;
		return data;
	}
}
