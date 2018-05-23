给定一个插入序列就可以唯一确定一棵二叉搜索树。然而，一棵给定的二叉搜索树却可以由多种不同的插入序列得到。
例如分别按照序列{2, 1, 3}和{2, 3, 1}插入初始为空的二叉搜索树，都得到一样的结果。于是对于输入的各种插入序列，你需要判断它们是否能生成一样的二叉搜索树。

输入格式:
输入包含若干组测试数据。每组数据的第1行给出两个正整数N (≤10)和L，分别是每个序列插入元素的个数和需要检查的序列个数。
第2行给出N个以空格分隔的正整数，作为初始插入序列。最后L行，每行给出N个插入的元素，属于L个需要检查的序列。

简单起见，我们保证每个插入序列都是1到N的一个排列。当读到N为0时，标志输入结束，这组数据不要处理。

输出格式:
对每一组需要检查的序列，如果其生成的二叉搜索树跟对应的初始序列生成的一样，输出“Yes”，否则输出“No”。

输入样例:
4 2
3 1 4 2
3 4 1 2
3 2 4 1
2 1
2 1
1 2
0
输出样例:
Yes
No
No

code:
#include <stdio.h>
#include <stdlib.h>

 typedef struct TNode{ 
	int data; 
	struct TNode* left;     
	struct TNode* right;  
 }*Position;
 typedef Position BinTree;

 BinTree Insert(BinTree BST, int x);
 int Compare(BinTree T1, BinTree T2);

int main(){
	int N, L;
	BinTree BST = NULL;
	int i = 0;
	do{
		scanf("%d", &N);
		if (N == 0) break;
		else{
			scanf("%d", &L);
			int x;
			for (i = 0; i < N; i++){
				scanf("%d", &x);
				BST = Insert(BST, x);
			}
		}
		int j;
		for (j = 0; j < L; j++){
			BinTree T = NULL;
			int d;
			int k;
			for (k = 0; k < N; k++){
				scanf("%d", &d);
				T = Insert(T, d);
			}
			if (Compare(BST, T)) printf("Yes\n");
			else printf("No\n");
		}
	} while (N != 0);
	
	return 0;
}

BinTree Insert(BinTree BST, int X)
{
	if (!BST){ /* 若原树为空，生成并返回一个结点的二叉搜索树 */
		BST = (BinTree)malloc(sizeof(struct TNode));
		BST->data = X;
		BST->left = BST->right = NULL;
	}
	else { /* 开始找要插入元素的位置 */
		if (X < BST->data)
			BST->left = Insert(BST->left, X);   /*递归插入左子树*/
		else  if (X > BST->data)
			BST->right = Insert(BST->right, X); /*递归插入右子树*/
		/* else x已经存在，什么都不做 */
	}
	return BST;
}
int Compare(BinTree T1, BinTree T2){
	if (T1 == NULL && T2 == NULL) return 1;//都空
	else if ((T1 != NULL && T2 == NULL) || (T1 == NULL && T2 != NULL)) return 0;//一个空一个不空
	else if (T1->data == T2->data) {//值相等，向子树递归
		return (Compare(T1->left, T2->left) && Compare(T1->right, T2->right));
	}else return 0;//值不等
}
