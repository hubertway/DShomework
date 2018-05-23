An AVL tree is a self-balancing binary search tree. 
In an AVL tree, the heights of the two child subtrees of any node differ by at most one; if at any time they differ by more than one, rebalancing is done to restore this property.
Figures 1-4 illustrate the rotation rules.
Now given a sequence of insertions, you are supposed to tell the root of the resulting AVL tree.

Input Specification:
Each input file contains one test case. For each case, the first line contains a positive integer N (≤20) which is the total number of keys to be inserted. 
Then N distinct integer keys are given in the next line. 
All the numbers in a line are separated by a space.

Output Specification:
For each test case, print the root of the resulting AVL tree in one line.

Sample Input 1:
5
88 70 61 96 120
Sample Output 1:
70
Sample Input 2:
7
88 70 61 96 120 90 65
Sample Output 2:
88

code:
#include <stdio.h>
#include <stdlib.h>
#define max(a,b) (((a)>(b))?(a):(b))

 typedef struct Node{ 
	int value,height; 
	struct Node* left;     
	struct Node* right;  
 }*Tnode;
 typedef Tnode AVL;

 Tnode newNode(int v);//生成新节点
 int getHeight(Tnode root);//获取以root为根的子树的当前height
 int getBalanceFactor(Tnode root);//计算结点root的平衡因子
 void updateHeight(Tnode root);//更新结点height
 void rotateLeft(Tnode *root);//左旋
 void rotateRight(Tnode *root);//右旋
 void insertNode(Tnode *root,int v);//插入权重为v的结点
 AVL Creat(int data[], int n);//读数组数据建树 

int main(){
	int N;
	scanf("%d", &N);
	int *data = (int*)malloc(sizeof(int)*N);
	int i;
	for (i = 0; i < N; i++){
		scanf("%d", &data[i]);
	}
	AVL Tree = Creat(data, N);
	printf("%d", Tree->value);
	return 0;
}

Tnode newNode(int v){
	Tnode node = (Tnode)malloc(sizeof(struct Node));
	node->value = v;
	node->height = 1;
	node->left = node->right = NULL;
	return node;
}
int getHeight(Tnode root){
	if (root == NULL) return 0;
	return root->height;
}
int getBalanceFactor(Tnode root){
	//左子树高度减右子树高度
	return getHeight(root->left) - getHeight(root->right);
}
void updateHeight(Tnode root){
	//max(右子树高，左子树)+1
	root->height = max(getHeight(root->left), getHeight(root->right))+1;
}
void rotateLeft(Tnode*root){
	Tnode tmp = (*root)->right;
	(*root)->right = tmp->left;
	tmp->left = (*root);
	updateHeight((*root));
	updateHeight(tmp);
	(*root) = tmp;
}
void rotateRight(Tnode *root){
	Tnode tmp = (*root)->left;
	(*root)->left = tmp->right;
	tmp->right = (*root);
	updateHeight((*root));
	updateHeight(tmp);
	(*root) = tmp;
}
void insertNode(Tnode *root, int v){
	if (*root == NULL){
		*root = newNode(v);
		return;
	}
	if (v < (*root)->value){//v比根节点权值小
		insertNode(&((*root)->left), v);
		updateHeight((*root));
		if (getBalanceFactor((*root)) == 2){
			if (getBalanceFactor((*root)->left) == 1){//LL型
				rotateRight(&(*root));
			}
			else if (getBalanceFactor((*root)->left) == -1){//LR型
				rotateLeft(&((*root)->left));
				rotateRight(&(*root));
			}
		}
	}
	if (v > (*root)->value){//v比根节点权值大
		insertNode(&((*root)->right), v);
		updateHeight(*root);
		if (getBalanceFactor((*root)) == -2){
			if (getBalanceFactor((*root)->right) == -1){//RR型
				rotateLeft(&(*root));
			}
			else if (getBalanceFactor((*root)->right) == 1){//RL型
				rotateRight(&((*root)->right));
				rotateLeft(&(*root));
			}
		}
	}
}
AVL Creat(int data[], int n){
	Tnode root = NULL;
	int i;
	for (i = 0; i < n; i++){
		insertNode(&root, data[i]);
	}
	return root;
}
