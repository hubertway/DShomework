
给定一个有N个顶点和E条边的无向图，请用DFS和BFS分别列出其所有的连通集。
假设顶点从0到N−1编号。进行搜索时，假设我们总是从编号最小的顶点出发，按编号递增的顺序访问邻接点。

输入格式:
输入第1行给出2个整数N(0<N≤10)和E，分别是图的顶点数和边数。随后E行，每行给出一条边的两个端点。每行中的数字之间用1空格分隔。
输出格式:
按照"{ v1 v2... vk}"的格式，每行输出一个连通集。先输出DFS的结果，再输出BFS的结果。

输入样例:
8 6
0 7
0 1
2 0
4 1
2 4
3 5
输出样例:
{ 0 1 4 2 7 }
{ 3 5 }
{ 6 }
{ 0 1 2 7 4 }
{ 3 5 }
{ 6 }

code:
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //这个头文件定义了bool, true, false等宏。
#define MaxVertex 10

typedef int Vertex; //用顶点下标表示顶点,为整型
typedef  struct ENode{//边的定义
	Vertex V1, V2; //有向边<V1, V2> 
}*PtrToENode;;
typedef PtrToENode Edge;

typedef struct GNode{//图结点的定义
	int Nv;  // 顶点数 
	int Ne;  //边数   
	int G[MaxVertex][MaxVertex]; //邻接矩阵 
}*PtrToGNode;
typedef PtrToGNode MGraph; 

typedef int Position;
typedef struct QNode{//队列定义
	int *Data;  //存储元素的数组 
	Position Front, Rear; // 队列的头、尾指针 
	int MaxSize; //队列最大容量 
}*Queue;
//建立图函数
MGraph CreateGraph(int VertexNum);
void InsertEdge(MGraph Graph, Edge E);
MGraph BuildGraph();
//图遍历函数
void Visit(Vertex V);
void DFS(MGraph Graph, Vertex V, void(*Visit)(Vertex));
bool IsEdge(MGraph Graph, Vertex V, Vertex W);
void BFS(MGraph Graph, Vertex S, void(*Visit)(Vertex));
//队列函数
Queue CreateQueue(int MaxSize);
bool IsEmpty(Queue Q);
void AddQ(Queue Q, int X);
int DeleteQ(Queue Q);

int N;//全局变量，顶点个数
int Visited[MaxVertex] = { false };//为全局变量，初始化为false

int main(){
	MGraph G =BuildGraph();
	int i;
	for (i = 0; i < N; i++){
		if (!Visited[i]){
			printf("{ ");
			DFS(G, i, Visit);
			printf("}\n");
		}
	}
	for (i = 0; i <MaxVertex; i++){//重置Visited[]
		Visited[i] = false;
	}
	for (i = 0; i < N; i++){
		if (!Visited[i]){
			printf("{ ");
			BFS(G, i, Visit);
			printf("}\n");
		}
	}
	return 0;
}

MGraph CreateGraph(int VertexNum){ 
	// 初始化一个有VertexNum个顶点但没有边的图 
	Vertex V, W;
	MGraph Graph;
	Graph = (MGraph)malloc(sizeof(struct GNode)); // 建立图 
	//初始化邻接矩阵
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	for (V = 0; V<Graph->Nv; V++)
	for (W = 0; W<Graph->Nv; W++)
		Graph->G[V][W] = 0;
	return Graph;
}
void InsertEdge(MGraph Graph, Edge E){
	Graph->G[E->V1][E->V2] = 1;
	Graph->G[E->V2][E->V1] = 1;//题设为无向图
}
MGraph BuildGraph(){
	MGraph Graph;
	Edge E;
	int Nv, i;

	scanf("%d", &Nv);   //读入顶点个数 
	N = Nv;
	Graph = CreateGraph(Nv); 
	scanf("%d", &(Graph->Ne));   //读入边数 
	if (Graph->Ne != 0) { // 如果有边 
		E = (Edge)malloc(sizeof(struct ENode)); //建立边结点 
		// 读入边，格式为"起点 终点 "，插入邻接矩阵 
		for (i = 0; i<Graph->Ne; i++) {
			scanf("%d %d", &E->V1, &E->V2);
			InsertEdge(Graph, E);
		}
	}
	return Graph;
}
void Visit(Vertex V){
	printf("%d ", V);
}
void DFS(MGraph Graph, Vertex V, void(*Visit)(Vertex)){
	//以V为出发点对邻接矩阵深度优先
	Visit(V);
	Visited[V] = true; // 标记S已访问 
	int i;
	for (i = 0; i < N;i++){
		if (Graph->G[V][i] && !Visited[i]){
			DFS(Graph,i, Visit);
		}
	}
}
bool IsEdge(MGraph Graph, Vertex V, Vertex W){
	//检查<V, W>是否图Graph中的一条边，即W是否V的邻接点
	return Graph->G[V][W]!=0 ? true : false;
}
void BFS(MGraph Graph, Vertex S, void(*Visit)(Vertex)){  
	//以S为出发点对邻接矩阵存储的图Graph进行BFS搜索 
	Queue Q;
	Vertex V, W;

	Q = CreateQueue(MaxVertex); // 创建空队列
	Visit(S);
	Visited[S] = true; // 标记S已访问 
	AddQ(Q, S); // S入队列 
	while (!IsEmpty(Q)) {
		V = DeleteQ(Q);  // 弹出V 
		for (W = 0; W<Graph->Nv; W++) //对图中的每个顶点W 
			// 若W是V的邻接点并且未访问过 
		if (!Visited[W] && IsEdge(Graph, V, W)) {
			// 访问顶点W 
			Visit(W);
			Visited[W] = true; // 标记W已访问 
			AddQ(Q, W); // W入队列
		}
	} 
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
