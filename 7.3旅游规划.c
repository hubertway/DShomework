有了一张自驾旅游路线图，你会知道城市间的高速公路长度、以及该公路要收取的过路费。
现在需要你写一个程序，帮助前来咨询的游客找一条出发地和目的地之间的最短路径。如果有若干条路径都是最短的，那么需要输出最便宜的一条路径。

输入格式:
输入数据的第1行给出4个正整数N、M、S、D，其中N（2≤N≤500）是城市的个数，顺便假设城市的编号为0~(N−1)；M是高速公路的条数；S是出发地的城市编号；D是目的地的城市编号。
随后的M行中，每行给出一条高速公路的信息，分别是：城市1、城市2、高速公路长度、收费额，中间用空格分开，数字均为整数且不超过500。输入保证解的存在。

输出格式:
在一行里输出路径的长度和收费总额，数字间以空格分隔，输出结尾不能有多余空格。

输入样例:
4 5 0 3
0 1 1 20
1 3 2 30
0 3 4 10
0 2 2 20
2 3 1 20
输出样例:
3 40

code:

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MaxVertexNum 501   
#define SuperBig 65535        
typedef int Vertex;         
typedef int WeightType;           

typedef struct ENode{
	Vertex V1, V2;     
	WeightType Dist;  //距离权重
	WeightType Cost;  //费用权重
 }*PtrToENode;
typedef PtrToENode Edge;

 typedef struct GNode{
	int Nv;  
	int Ne;  
	WeightType GDist[MaxVertexNum][MaxVertexNum];
	WeightType GCost[MaxVertexNum][MaxVertexNum];
 }*PtrToGNode;
typedef PtrToGNode MGraph; 

MGraph CreateGraph(int VertexNum);
void InsertEdge(MGraph Graph, Edge E);
MGraph BuildGraph();
Vertex FindMinDist(MGraph Graph, int collected[]);
void Dijkstra(MGraph Graph, Vertex S);

int N, M, S, D;
int dist[MaxVertexNum];
int path[MaxVertexNum];//记录路径，其实没用到，但记下来无妨
int cost[MaxVertexNum] = {0};

int main(){
	scanf("%d %d %d %d", &N, &M, &S, &D);
	int i;
	for (i = 0; i < MaxVertexNum; i++) dist[i] = -1;//初始化dist[]
	MGraph G = BuildGraph();
	Dijkstra(G, S);
	printf("%d %d\n", dist[D], cost[D]);
	return 0;
}

MGraph CreateGraph(int VertexNum){
	Vertex V, W;
	MGraph Graph;
	Graph = (MGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	for (V = 0; V<Graph->Nv ; V++)
	for (W = 0; W < Graph->Nv; W++){
		Graph->GCost[V][W] = SuperBig;
		Graph->GDist[V][W] = SuperBig;
	}	
	return Graph;
}
void InsertEdge(MGraph Graph, Edge E){
	Graph->GDist[E->V1][E->V2] = E->Dist;
	Graph->GDist[E->V2][E->V1] = E->Dist;
	Graph->GCost[E->V1][E->V2] = E->Cost;
	Graph->GCost[E->V2][E->V1] = E->Cost;
}
MGraph BuildGraph(){
	MGraph Graph;
	Edge E;
	int  i;	
	Graph = CreateGraph(N);
	Graph->Ne = M;
	if (Graph->Ne != 0) {
		E = (Edge)malloc(sizeof(struct ENode));
		for (i = 0; i<Graph->Ne; i++) {
			scanf("%d %d %d %d", &E->V1, &E->V2, &E->Dist, &E->Cost);
			InsertEdge(Graph, E);
		}
	}
	return Graph;
}
Vertex FindMinDist(MGraph Graph,  int collected[]){ 
	// 返回未被收录顶点中dist最小者 
	Vertex MinV, V;
	int MinDist = SuperBig;

	for (V = 0; V<Graph->Nv; V++) {
		if (collected[V] == false && dist[V]<MinDist) {
			// 若V未被收录，且dist[V]更小 
			MinDist = dist[V]; //更新最小距离 
			MinV = V; // 更新对应顶点 
		}
	}
	if (MinDist <SuperBig)
	return MinV; // 返回对应的顶点下标 
	else return  -1;
}
void Dijkstra(MGraph Graph, Vertex S){
	int collected[MaxVertexNum];
	Vertex V, W;
	//初始化：此处默认邻接矩阵中不存在的边用SuperBig表示 
	for (V = 0; V<Graph->Nv; V++) {
		dist[V] = Graph->GDist[S][V];
		cost[V] = Graph->GCost[S][V];
		if (dist[V]<SuperBig)
			path[V] = S;
		else
			path[V] = -1;
		collected[V] = false;
	}
	// 先将起点收入集合 
	dist[S] = 0;
	collected[S] = true;

	while (1) {
		// V = 未被收录顶点中dist最小者 
		V = FindMinDist(Graph, collected);
		if (V == -1) //若这样的V不存在
			break;      // 算法结束
		collected[V] = true;  // 收录V 

		for (W = 0; W<Graph->Nv; W++) // 对图中的每个顶点W 
			// 若W是V的邻接点并且未被收录
		if (collected[W] == false && Graph->GDist[V][W]<SuperBig) {
			// 若收录V使得dist[W]变小
			if (dist[V] + Graph->GDist[V][W] < dist[W]) {
				dist[W] = dist[V] + Graph->GDist[V][W]; //更新dist[W] 
				path[W] = V; // 更新S到W的路径 
				cost[W] = cost[V] + Graph->GCost[V][W];//更新S到W的费用
			}
			else if ((dist[V] + Graph->GDist[V][W] == dist[W])  //等长且更新费用减少
				&& (cost[V] + Graph->GCost[V][W] < cost[W])){
				cost[W] = cost[V] + Graph->GCost[V][W];
				path[W] = V;
			}
		}
	}  
}
