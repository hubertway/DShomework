Given the relations of all the activities of a project, you are supposed to find the earliest completion time of the project.

Input Specification:
Each input file contains one test case.
Each case starts with a line containing two positive integers N (≤100), the number of activity check points (hence it is assumed that the check points are numbered from 0 to N−1), and M, the number of activities. 
Then M lines follow, each gives the description of an activity. 
For the i-th activity, three non-negative numbers are given: S[i], E[i], and L[i], where S[i] is the index of the starting check point, E[i] of the ending check point, and L[i] the lasting time of the activity. 
The numbers in a line are separated by a space.

Output Specification:
For each test case, if the scheduling is possible, print in a line its earliest completion time; or simply output "Impossible".

Sample Input 1:
9 12
0 1 6
0 2 4
0 3 5
1 4 1
2 4 1
3 5 2
5 4 0
4 6 9
4 7 7
5 7 4
6 8 2
7 8 4
Sample Output 1:
18
Sample Input 2:
4 5
0 1 1
0 2 2
2 1 3
1 3 4
3 2 5
Sample Output 2:
Impossible

code:
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxVertexNum 1001   
#define INFINITY 65535  
typedef int Vertex;
typedef int WeightType;

typedef struct ENode{
	Vertex V1, V2;
	WeightType Cost;
}*PtrToENode;
typedef PtrToENode Edge;

typedef struct AdjVNode{ //邻接点的定义 
	Vertex AdjV;       //邻接点下标 
	WeightType Cost;  // 边权重 
	struct AdjVNode* Next;    //指向下一个邻接点的指针
}*PtrToAdjVNode;

typedef struct Vnode{ //顶点表头结点的定义 
	PtrToAdjVNode FirstEdge;// 边表头指针
} AdjList[MaxVertexNum];    // AdjList是邻接表类型

typedef struct GNode{
	int Nv;
	int Ne;
	AdjList G;
} *PtrToGNode;
typedef PtrToGNode LGraph;

LGraph CreateGraph(int VertexNum);
void InsertEdge(LGraph Graph, Edge E);
LGraph BuildGraph();

typedef struct QNode{
	int *Data;
	int Front, Rear;
	int MaxSize;
}*Queue;

Queue CreateQueue(int MaxSize);
bool IsEmpty(Queue Q);
void AddQ(Queue Q, int X);
int DeleteQ(Queue Q);

bool TopSort(LGraph Graph, Vertex TopOrder[]);
int NeedDay[MaxVertexNum] = { 0 };

int main(){
	LGraph G = BuildGraph();
	Vertex TopOrder[MaxVertexNum];
	bool answer = TopSort(G, TopOrder);
	if (answer){
		int max=0;
		int i;
		for (i = 0; i < G->Nv; i++)
			if (max < NeedDay[i]) max = NeedDay[i];//找到 NeedDay[]中最大值
		printf("%d\n", max);
	}
	else printf("Impossible\n");

	return 0;
}
LGraph CreateGraph(int VertexNum){
	//初始化一个有VertexNum个顶点但没有边的图 
	Vertex V;
	LGraph Graph;
	Graph = (LGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	//初始化邻接表头指针,顶点编号从0开始
	for (V = 0; V<Graph->Nv; V++)
		Graph->G[V].FirstEdge = NULL;

	return Graph;
}
void InsertEdge(LGraph Graph, Edge E){
	PtrToAdjVNode NewNode;
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V2;
	NewNode->Cost = E->Cost;
	// 将V2插入V1的表头 ,有向图，不能也不用将V1插入V2
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;
}
LGraph BuildGraph(){
	LGraph Graph;
	Edge E;
	int Nv, i;
	scanf("%d", &Nv);
	Graph = CreateGraph(Nv);
	scanf("%d", &(Graph->Ne));
	if (Graph->Ne != 0) {
		E = (Edge)malloc(sizeof(struct ENode));
		for (i = 0; i<Graph->Ne; i++) {
			scanf("%d %d %d", &E->V1, &E->V2, &E->Cost);
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

bool TopSort(LGraph Graph, Vertex TopOrder[]){
	// 对Graph进行拓扑排序,  TopOrder[]顺序存储排序后的顶点下标 
	int Indegree[MaxVertexNum], cnt; // Indegree[]入度
	Vertex V;
	PtrToAdjVNode W;
	Queue Q = CreateQueue(Graph->Nv);
	// 初始化Indegree[] 
	for (V = 0; V<Graph->Nv; V++)
		Indegree[V] = 0;
	// 遍历图，得到Indegree[]
	for (V = 0; V<Graph->Nv; V++)
	for (W = Graph->G[V].FirstEdge; W; W = W->Next)
		Indegree[W->AdjV]++; //对有向边<V, W->AdjV>累计 终点 的入度 

	for (V = 0; V < Graph->Nv; V++)	{
		if (Indegree[V] == 0){// 将所有入度为0的顶点入列
			AddQ(Q, V);
		}
	}
	//下面进入拓扑排序
	cnt = 0;
	while (!IsEmpty(Q)){
		V = DeleteQ(Q); // 弹出一个入度为0的顶点 
		TopOrder[cnt++] = V; // 将之存为结果序列的下一个元素
		// 对V的每个邻接点W->AdjV 
		for (W = Graph->G[V].FirstEdge; W; W = W->Next)
		if (--Indegree[W->AdjV] == 0){// 若删除V使得W->AdjV入度为0 
			if (NeedDay[W->AdjV] < W->Cost + NeedDay[V])
				NeedDay[W->AdjV] = W->Cost + NeedDay[V];
			AddQ(Q, W->AdjV); //则该顶点入列
		}
	} //while结束

	if (cnt != Graph->Nv)
		return false; // 说明图中有回路, 返回不成功标志
	else
		return true;
}
