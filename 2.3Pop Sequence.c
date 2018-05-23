Given a stack which can keep M numbers at most. Push N numbers in the order of 1, 2, 3, ..., N and pop randomly.
You are supposed to tell if a given sequence of numbers is a possible pop sequence of the stack.
For example, if M is 5 and N is 7, we can obtain 1, 2, 3, 4, 5, 6, 7 from the stack, but not 3, 2, 1, 7, 5, 6, 4.

Input Specification:
Each input file contains one test case. For each case, the first line contains 3 numbers (all no more than 1000): M (the maximum capacity of the stack), N (the length of push sequence), and K (the number of pop sequences to be checked). Then K lines follow, each contains a pop sequence of N numbers. All the numbers in a line are separated by a space.

Output Specification:
For each pop sequence, print in one line "YES" if it is indeed a possible pop sequence of the stack, or "NO" if not.

Sample Input:
5 7 5
1 2 3 4 5 6 7
3 2 1 7 5 6 4
7 6 5 4 3 2 1
5 6 4 3 7 2 1
1 7 6 5 4 3 2
Sample Output:
YES
NO
NO
YES
NO

/*分析：按照要求进行模拟。
先把输入的序列接收进数组v。
然后按顺序1~n把数字进栈，每进入一个数字，判断有没有超过最大范围，超过了就break。
如果没超过，设current = 1，从数组的第一个数字开始，看看是否与栈顶元素相等，
while相等就一直弹出栈，不相等就继续按顺序把数字压入栈
最后根据变量flag的值输出yes或者no
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Snode{
	int data;
	struct Snode * next;
}*Prt;
typedef Prt Stack;

Stack Createstack();//建立堆栈
int IsEmpty(Stack S);//判空
void Push(Stack S, int X);//入栈
void Pop(Stack S);//出栈
int Size(Stack S);//测量堆栈内元素个数
int Top(Stack S);//读取栈顶元素

int main(){
	int m, n, k;
	scanf("%d %d %d", &m, &n, &k);
	for (int i = 0; i < k; i++){
		int flag = 0;//判断最终结果
		Stack S = Createstack();
		int *a = (int*)malloc(sizeof(int)*(n + 1));
		//创建长度为n+1的数组,a[0]抛弃，方便从1开始计数
		for (int j = 1; j <= n;j++){
			scanf("%d", &a[j]);
		}
		int now = 1;//从数组第一个开始，检查是否与栈顶元素相等；
		for (int k = 1; k <= n; k++){
			Push( S , k );//从1开始顺序入栈
			if (Size(S) > m) break;
			while (!IsEmpty(S) && Top(S) == a[now]){
				Pop(S);
				now++;
			}
		}
		if (now == n + 1) flag = 1;
		if (flag) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
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
void Pop(Stack S){
	Prt FstC;
	if (IsEmpty(S) == 0){
		FstC = S->next;
		S->next = FstC->next;
	}
}
int Size(Stack S){
	int cnt = 0;
	Prt Tmp = S;
	while (IsEmpty(Tmp) == 0){
			cnt++;
			Tmp = Tmp->next;
	}
	 return cnt;
}
int Top(Stack S){
	int data;
	if (IsEmpty(S) == 0){
		data = S->next ->data;
		return data;
	}
  //return 0;
}
