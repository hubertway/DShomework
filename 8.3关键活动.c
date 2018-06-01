假定一个工程项目由一组子任务构成，子任务之间有的可以并行执行，有的必须在完成了其它一些子任务后才能执行。
“任务调度”包括一组子任务、以及每个子任务可以执行所依赖的子任务集。

比如完成一个专业的所有课程学习和毕业设计可以看成一个本科生要完成的一项工程，各门课程可以看成是子任务。
有些课程可以同时开设，比如英语和C程序设计，它们没有必须先修哪门的约束；有些课程则不可以同时开设，因为它们有先后的依赖关系，比如C程序设计和数据结构两门课，必须先学习前者。

但是需要注意的是，对一组子任务，并不是任意的任务调度都是一个可行的方案。
比如方案中存在“子任务A依赖于子任务B，子任务B依赖于子任务C，子任务C又依赖于子任务A”，那么这三个任务哪个都不能先执行，这就是一个不可行的方案。

任务调度问题中，如果还给出了完成每个子任务需要的时间，则我们可以算出完成整个工程需要的最短时间。
在这些子任务中，有些任务即使推迟几天完成，也不会影响全局的工期；但是有些任务必须准时完成，否则整个项目的工期就要因此延误，这种任务就叫“关键活动”。

请编写程序判定一个给定的工程项目的任务调度是否可行；如果该调度方案可行，则计算完成整个工程项目需要的最短时间，并输出所有的关键活动。

输入格式:
输入第1行给出两个正整数N(≤100)和M，其中N是任务交接点（即衔接相互依赖的两个子任务的节点，例如：若任务2要在任务1完成后才开始，则两任务之间必有一个交接点）的数量。交接点按1~N编号，M是子任务的数量，依次编号为1~M。随后M行，每行给出了3个正整数，分别是该任务开始和完成涉及的交接点编号以及该任务所需的时间，整数间用空格分隔。

输出格式:
如果任务调度不可行，则输出0；否则第1行输出完成整个工程项目需要的时间，第2行开始输出所有关键活动，每个关键活动占一行，按格式“V->W”输出，其中V和W为该任务开始和完成涉及的交接点编号。关键活动输出的顺序规则是：任务开始的交接点编号小者优先，起点编号相同时，与输入时任务的顺序相反。

输入样例:
7 8
1 2 4
1 3 3
2 4 5
3 4 3
4 5 1
4 6 6
5 7 5
6 7 2
输出样例:
17
1->2
2->4
4->6
6->7

code:

#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

#define MAXVER 101
#define INFINITY 65535
#define FindMax(a,b) ((a)>(b))?(a):(b)
#define FindMin(a,b) ((a)<(b))?(a):(b)

int G[MAXVER][MAXVER];  //图
int early[MAXVER];      //最早完成时间
int late[MAXVER];      //最晚完成时间
int in[MAXVER];        //入度
int out[MAXVER];       //出度
int nv, ne;            //顶点数目 ，边数目

void CreatGraph();
int EarlyTime();
void LateTime(int SumCost);

typedef struct QNode{
	int *Data;
	int Front, Rear;
	int MaxSize;
}*Queue;

Queue CreateQueue(int MaxSize);
bool IsEmpty(Queue Q);
void AddQ(Queue Q, int X);
int DeleteQ(Queue Q);

int main(){
	scanf("%d %d", &nv, &ne);
	CreatGraph();
	int time;
	time = EarlyTime();
	if (time == -1) printf("0\n");
	else{
		printf("%d\n", time);
		LateTime(time);
		int i, j;
		for (i = 1; i <= nv; i++){
			if (early[i] != late[i])  //找到关键路径结点
				continue;
			for (j = nv; j >= 1; j--){ //题目要求起点编号相同时,与输入时任务的顺序相反,故j反向遍历
				if (G[i][j] >= 0 &&  // i,j邻接
					early[j] == late[j] && // j也是关键路径结点
					late[j] - G[i][j] == early[i]){// i,j符合关键路径关系
					printf("%d->%d\n", i, j);
				}
			}
		}
	}
	return 0;
}

void CreatGraph(){
	int i, j;
	int V, W, Cost;
	for (i = 1; i <= nv; i++){//初始化
		for (j = 1; j <= nv; j++)
				G[i][j] = -1;
		early[i] = 0;
		late[i] = INFINITY;
		in[i] = 0;
		out[i] = 0;
	}
	for (i = 0; i<ne; i++){//读入数据，更新出/入度
		scanf("%d %d %d", &V, &W, &Cost);
		G[V][W] = Cost;   //有向边
		in[W] ++;
		out[V]++;
	}
}
int EarlyTime(){
	Queue Q = CreateQueue(nv);
	int count = 0;
	int i ,temp,time;
	for (i = 1; i <= nv; i++)
		if (in[i] == 0) //如果入度为0则入队
			AddQ(Q, i);
	while (!IsEmpty(Q)) {
		temp = DeleteQ(Q);  
		count++;
		for (i = 1; i <= nv; i++){
			if (G[temp][i] >= 0){
				in[i]--;
				early[i] = FindMax(early[i], early[temp] + G[temp][i]);
				if (in[i] == 0)
					AddQ(Q, i);
			}
		}
	}
	if (count != nv) return -1;
	else {
		time = early[1];
		for (i = 2; i <= nv; i++) //寻找最大时间长度
			if (early[i] > time) time = early[i];
		return time;
	}
}
void LateTime(int SumCost){
	Queue Q = CreateQueue(MAXVER);
	int i, temp;
	for (i = 1; i <= nv; i++){
		if (out[i] == 0){
			AddQ(Q, i);
			late[i] = SumCost;
		}
	}
	while (!IsEmpty(Q)){
		temp = DeleteQ(Q);
		for (i = nv; i >= 1; i--){
			if (G[i][temp] >= 0){
				late[i] = FindMin(late[i], late[temp] - G[i][temp]);
				out[i]--;
				if (out[i] == 0)
					AddQ(Q, i);
			}
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
