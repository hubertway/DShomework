现有村落间道路的统计数据表中，列出了有可能建设成标准公路的若干条道路的成本，求使每个村落都有公路连通所需要的最低成本。

输入格式:
输入数据包括城镇数目正整数N（≤1000）和候选道路数目M（≤3N）；
随后的M行对应M条道路，每行给出3个正整数，分别是该条道路直接连通的两个城镇的编号以及该道路改建的预算成本。为简单起见，城镇从1到N编号。

输出格式:
输出村村通需要的最低成本。如果输入数据不足以保证畅通，则输出−1，表示需要建设更多公路。

输入样例:
6 15
1 2 5
1 3 3
1 4 7
1 5 4
1 6 2
2 3 4
2 4 6
2 5 2
2 6 6
3 4 6
3 5 1
3 6 1
4 5 10
4 6 8
5 6 3
输出样例:
12

code:
#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 1001   
#define INFINITY 65535  
#define ERROR -1
typedef int Vertex;
typedef int WeightType;

typedef struct ENode{
	Vertex V1, V2;
	WeightType Cost;
}*PtrToENode;
typedef PtrToENode Edge;

typedef struct GNode{
	int Nv;
	int Ne;
	WeightType G[MaxVertexNum][MaxVertexNum];
}*PtrToGNode;
typedef PtrToGNode MGraph;

MGraph CreateMGraph(int VertexNum);
void InsertMEdge(MGraph Graph, Edge E);
MGraph BuildMGraph();

typedef struct AdjVNode{ //邻接点的定义 
	Vertex AdjV;       //邻接点下标 
	WeightType Cost;  // 边权重 
	struct AdjVNode* Next;    //指向下一个邻接点的指针
}*PtrToAdjVNode;

typedef struct Vnode{ //顶点表头结点的定义 
	PtrToAdjVNode FirstEdge;// 边表头指针
} AdjList[MaxVertexNum];    // AdjList是邻接表类型

typedef struct LGNode{ //图结点的定义 
	int Nv;     // 顶点数 
	int Ne;     //边数   
	AdjList G;  // 邻接表 
} *LPtrToGNode;
typedef LPtrToGNode LGraph; // 以邻接表方式存储的图类型

LGraph CreateLGraph(int VertexNum);
void InsertLEdge(LGraph Graph, Edge E);
Vertex FindMinDist(MGraph Graph, WeightType dist[]);
int Prim(MGraph Graph, LGraph MST);
int N, M;

int main(){
	scanf("%d %d", &N, &M);
	MGraph G = BuildMGraph();
	LGraph MST = NULL;
	int SumCost =  Prim(G, MST);
	if (SumCost != ERROR) printf("%d\n", SumCost);
	else printf("-1\n");
	return 0;
}

MGraph CreateMGraph(int VertexNum){
	Vertex V, W;
	MGraph Graph;
	Graph = (MGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	for (V = 0; V<Graph->Nv; V++)
	for (W = 0; W < Graph->Nv; W++){
		Graph->G[V][W] = INFINITY;
	}
	return Graph;
}
void InsertMEdge(MGraph Graph, Edge E){
	Graph->G[E->V1][E->V2] = E->Cost;
	Graph->G[E->V2][E->V1] = E->Cost;
}
MGraph BuildMGraph(){
	MGraph Graph;
	Edge E;
	int  i;
	Graph = CreateMGraph(N);
	Graph->Ne = M;
	if (Graph->Ne != 0) {
		E = (Edge)malloc(sizeof(struct ENode));
		for (i = 0; i<Graph->Ne; i++) {
			scanf("%d %d %d", &E->V1, &E->V2, &E->Cost);
			E->V1--; E->V2--;
			InsertMEdge(Graph, E);
		}
	}
	return Graph;
}
LGraph CreateLGraph(int VertexNum){
	//初始化一个有VertexNum个顶点但没有边的图 
	Vertex V;
	LGraph Graph;
	Graph = (LGraph)malloc(sizeof(struct GNode)); // 建立图 
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	//初始化邻接表头指针,顶点编号从0开始
	for (V = 0; V<Graph->Nv; V++)
		Graph->G[V].FirstEdge = NULL;

	return Graph;
}
void InsertLEdge(LGraph Graph, Edge E){
	PtrToAdjVNode NewNode;
	// 插入边 <V1, V2> , 为V2建立新的邻接点 
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V2;
	NewNode->Cost = E->Cost;
	// 将V2插入V1的表头 
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;

	//无向图，还要插入边 <V2, V1> 
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V1;
	NewNode->Cost = E->Cost;
	// 将V1插入V2的表头 
	NewNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = NewNode;
}

Vertex FindMinDist(MGraph Graph, WeightType dist[]){
	// 返回未被收录顶点中dist最小者
	Vertex MinV, V;
	WeightType MinDist = INFINITY;

	for (V = 0; V<Graph->Nv; V++) {
		if (dist[V] != 0 && dist[V]<MinDist) {
			// 若V未被收录，且dist[V]更小 
			MinDist = dist[V]; // 更新最小距离 
			MinV = V; // 更新对应顶点 
		}
	}
	if (MinDist < INFINITY) // 若找到最小dist
		return MinV; //返回对应的顶点下标 
	else return ERROR;  // 若这样的顶点不存在，返回-1作为标记
}

int Prim(MGraph Graph, LGraph MST){ 
	// 将最小生成树保存为邻接表存储的图MST，返回最小权重和 
	WeightType dist[MaxVertexNum], TotalWeight;  // dist[V]定义为 一个顶点V到最小生成树的距离（边的权重）
	Vertex parent[MaxVertexNum], V, W;  // parent[V]定义为 第个顶点V的parent下标，类似并查集概念
	int VCount;
	Edge E;
	// 初始化。默认初始点下标是0 
	for (V = 0; V<Graph->Nv; V++) {
		dist[V] = Graph->G[0][V];
		parent[V] = 0; // 暂且定义所有顶点的父结点都是初始点0 
	}
	TotalWeight = 0; // 初始化权重和 
	VCount = 0;      // 初始化收录的顶点数
	MST = CreateLGraph(Graph->Nv);// 用邻接表创建包含所有顶点但没有边的图。
	E = (Edge)malloc(sizeof(struct ENode)); // 建立空的边结点
	//将初始点0收录进MST
	dist[0] = 0;
	VCount++;
	parent[0] = -1; // 当前树根是0 

	while (1) {
		V = FindMinDist(Graph, dist);
		if (V == ERROR) //若这样的V不存在 
			break;   
		// 将V及相应的边<parent[V], V>收录进MST 
		E->V1 = parent[V];
		E->V2 = V;
		E->Cost = dist[V];
		InsertLEdge(MST, E);
		TotalWeight += dist[V];
		dist[V] = 0;
		VCount++;

		for (W = 0; W<Graph->Nv; W++) //对图中的每个顶点W 
		if (dist[W] != 0 && Graph->G[V][W]<INFINITY) {
			// 若W是V的邻接点并且未被收录 
			if (Graph->G[V][W] < dist[W]) {
				// 若收录V使得dist[W]变小
				dist[W] = Graph->G[V][W]; // 更新dist[W] 
				parent[W] = V; // 更新树 
			}
		}
	} // while结束
	if (VCount < Graph->Nv) // MST中收的顶点不到|V|个
		TotalWeight = ERROR;
	return TotalWeight;   // 算法执行完毕，返回最小权重和或错误标记
}
