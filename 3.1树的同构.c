给定两棵树T1和T2。如果T1可以通过若干次左右孩子互换就变成T2，则我们称两棵树是“同构”。现给定两棵树，请你判断它们是否是同构的。
输入格式:
输入给出2棵二叉树树的信息。对于每棵树，首先在一行中给出一个非负整数N (≤10)，即该树的结点数（此时假设结点从0到N−1编号）；
随后N行，第i行对应编号第i个结点，给出该结点中存储的1个英文大写字母、其左孩子结点的编号、右孩子结点的编号。如果孩子结点为空，则在相应位置上给出“-”。
给出的数据间用一个空格分隔。注意：题目保证每个结点中存储的字母是不同的。
输出格式:
如果两棵树是同构的，输出“Yes”，否则输出“No”。

输入样例1：
8
A 1 2
B 3 4
C 5 -
D - -
E 6 -
G 7 -
F - -
H - -
8
G - 4
B 7 6
F - -
A 5 1
H - -
C 0 -
D - -
E 2 -
输出样例1:
Yes
输入样例2（对应图2）：
8
B 5 7
F - -
A 0 3
C 6 -
H - -
D - -
G 4 -
E 1 -
8
D 6 -
B 5 -
E - -
H - -
C 0 2
G - 3
F - -
A 1 4
输出样例2:
No

code:
#include <stdio.h>
#include <stdlib.h>

#define MaxTree 10
#define Null -1
#define Tree int
typedef struct Tnode{
	char data;
	Tree left;
	Tree right; 
} BinTree;

Tree Build(BinTree T[]);//建树
int Isomorphic(Tree R1, Tree R2, BinTree T1[], BinTree T2[]);

int main(){
	Tree R1, R2;
	BinTree T1[MaxTree], T2[MaxTree];
	R1 = Build(T1);
	R2 = Build(T2);
	if (Isomorphic(R1, R2, T1, T2)) printf("Yes\n");
	else printf("No\n");

	return 0;
}

Tree Build(BinTree T[]){
	int num;
	int root = Null;
	scanf("%d", &num);
	if (num){
		int i;
		char cl, cr;
		int *check = (int*)malloc(sizeof(int)*num);
		//为了查找根节点建立check数组
		for (i = 0; i < num; i++) check[i] = 0;
		for (i = 0; i < num; i++){
			scanf("\n%c %c %c", &T[i].data, &cl, &cr);
			//加上'\n'是为了避免T[i].data误读，为了处理'-'，都用char型读入后处理
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
			if (!check[i]) break;
			//不为零的即没有其他节点指向它，故为根节点
		}
		root = i;
	}
	return root;
}
int Isomorphic(Tree R1, Tree R2, BinTree T1[], BinTree T2[]){
	if ((R1 == Null) && (R2 == Null)) return 1;//两棵树都空，同构
	if ((R1 == Null) && (R2 != Null) || (R1 != Null) && (R2 == Null))
		return 0;//一个树空，一个不空，不同构
	if (T1[R1].data != T2[R2].data) return 0;//树根节点值不同，必然不同构
	if ((T1[R1].left == Null) && (T2[R2].right == Null))
		return Isomorphic(T1[R1].right, T2[R2].right ,T1,T2 );
	if (((T1[R1].left != Null) && (T2[R2].left != Null)) &&
		((T1[T1[R1].left].data == T2[T2[R2].left].data)))
		//两个树的左子树同时不空，且值相同
		return (Isomorphic(T1[R1].left, T2[R2].left, T1, T2) &&
				Isomorphic(T1[R1].right, T2[R2].right, T1, T2));
	else//两个树的左子树同时不空,值不同，可能是交换了
		return(Isomorphic(T1[R1].left, T2[R2].right, T1, T2) &&
			   Isomorphic(T1[R1].right, T2[R2].left, T1, T2));
}
