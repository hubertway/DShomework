“六度空间”理论又称作“六度分隔（Six Degrees of Separation）”理论。
这个理论可以通俗地阐述为：“你和任何一个陌生人之间所间隔的人不会超过六个，也就是说，最多通过五个人你就能够认识任何一个陌生人。”
“六度空间”理论虽然得到广泛的认同，并且正在得到越来越多的应用。但是数十年来，试图验证这个理论始终是许多社会学家努力追求的目标。然而由于历史的原因，这样的研究具有太大的局限性和困难。随着当代人的联络主要依赖于电话、短信、微信以及因特网上即时通信等工具，能够体现社交网络关系的一手数据已经逐渐使得“六度空间”理论的验证成为可能。

假如给你一个社交网络图，请你对每个节点计算符合“六度空间”理论的结点占结点总数的百分比。

输入格式:
输入第1行给出两个正整数，分别表示社交网络图的结点数N（1<N≤10^4，表示人数）、边数M（≤33×N，表示社交关系数）。
随后的M行对应M条边，每行给出一对正整数，分别是该条边直接连通的两个结点的编号（节点从1到N编号）。

输出格式:
对每个结点输出与该结点距离不超过6的结点数占结点总数的百分比，精确到小数点后2位。每个结节点输出一行，格式为“结点编号:（空格）百分比%”。

输入样例:
10 9
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
输出样例:
1: 70.00%
2: 80.00%
3: 90.00%
4: 100.00%
5: 100.00%
6: 100.00%
7: 100.00%
8: 90.00%
9: 80.00%
10: 70.00%

code:
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#define MaxVertex 10001

typedef int Vertex; 
typedef  struct ENode{//图边
	Vertex V1, V2; 
}*PtrToENode;
typedef PtrToENode Edge;

typedef struct GNode{//图结点
	int Nv;  
	int Ne;   
	int G[MaxVertex][MaxVertex]; //邻接矩阵 
}*PtrToGNode;
typedef PtrToGNode MGraph;

typedef int Position;
typedef struct QNode{//队列
	int *Data;  
	Position Front, Rear; 
	int MaxSize; 
}*Queue;

MGraph CreateGraph(int VertexNum);
void InsertEdge(MGraph Graph, Edge E);
MGraph BuildGraph();

Queue CreateQueue(int MaxSize);
bool IsEmpty(Queue Q);
void AddQ(Queue Q, int X);
int DeleteQ(Queue Q);

bool IsEdge(MGraph Graph, Vertex V, Vertex W);
int BFS(MGraph Graph, Vertex S);
void SDS(MGraph Graph);

int Visited[MaxVertex] = { false };

int main(){
	MGraph G = BuildGraph();
	SDS(G);
	return 0;
}

MGraph CreateGraph(int VertexNum){
	Vertex V, W;
	MGraph Graph;
	Graph = (MGraph)malloc(sizeof(struct GNode)); 
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	//结点从1-N编号
	for (V = 1; V<Graph->Nv+1; V++)
	for (W = 1; W<Graph->Nv+1; W++)
		Graph->G[V][W] = 0;
	return Graph;
}
void InsertEdge(MGraph Graph, Edge E){
	Graph->G[E->V1][E->V2] = 1;
	Graph->G[E->V2][E->V1] = 1;
}
MGraph BuildGraph(){
	MGraph Graph;
	Edge E;
	int Nv, i;
	scanf("%d", &Nv);  
	Graph = CreateGraph(Nv);
	scanf("%d", &(Graph->Ne));  
	if (Graph->Ne != 0) { // 如果有边 
		E = (Edge)malloc(sizeof(struct ENode));
		for (i = 0; i<Graph->Ne; i++) {
			scanf("%d %d", &E->V1, &E->V2);
			InsertEdge(Graph, E);
		}
	}
	return Graph;
}
Queue CreateQueue(int MaxSize){
	Queue Q = (Queue)malloc(sizeof(struct QNode));
	Q->Data = (int *)malloc(MaxSize * sizeof(int));
	Q->Front = Q->Rear = 0;
	Q->MaxSize = MaxSize;
	return Q;
}
void AddQ(Queue Q, int X){
	Q->Rear = (Q->Rear + 1) % (Q->MaxSize);
	Q->Data[Q->Rear] = X;
}
bool IsEmpty(Queue Q){
	return (Q->Front == Q->Rear);
}
int DeleteQ(Queue Q){
	Q->Front = (Q->Front + 1) % Q->MaxSize;
	return  Q->Data[Q->Front];
}
bool IsEdge(MGraph Graph, Vertex V, Vertex W){
	return Graph->G[V][W] != 0 ? true : false;
}
int BFS(MGraph Graph, Vertex S){
	Queue Q;
	Vertex V, W;
	Q = CreateQueue(MaxVertex); 
	Visited[S] = true; 
	int count, level, last,tail=0;
	count = 1;
	level = 0;
	last = S;
	AddQ(Q, S); 
	while (!IsEmpty(Q)) {
		V = DeleteQ(Q);  
		for (W = 1; W<Graph->Nv+1; W++) 
		if (!Visited[W] && IsEdge(Graph, V, W)) {
			Visited[W] = true; 
			AddQ(Q, W);
			count++;
			tail = W;
		}
		if (V == last) {
			level++;
			last = tail;
		}
		if (level == 6) break;
	}
	return count;
}
void SDS(MGraph Graph){
	Vertex W;
	int count;
	double Per;
	for (W = 1; W < Graph->Nv+1; W++){
		count = BFS(Graph, W);
		Pe r = 100 * (double)count / Graph->Nv;
		printf("%d: %.2f%%\n", W, Per);
		int i;//重置Visited
		for (i = 0; i <MaxVertex; i++){
			Visited[i] = false;
		}
	}
}
