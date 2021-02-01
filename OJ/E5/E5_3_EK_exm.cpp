//Ford-Fulkerson方法
//为什么叫Ford-Fulkerson方法而不是算法，原因在于可以用多种方式实现这一方法，
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

const int N = 505;
const int INF = 1000000; //无穷大
int n, m, start, eend;
int mmap[N][N], path[N], flow[N];
queue<int> q; //先进先出队列——用于表达节点搜索顺序

//广度优先搜索
int bfs(){
	int i, t;
	while( !q.empty() ) q.pop();
	memset(path, -1, sizeof(path));
	path[start] = 0;
	flow[start] = INF;
	q.push( start );
	while( !q.empty() )    {
		t = q.front();				//取队列的首元素
		q.pop();					//把队列首元素弹出
		if(t == eend) break;
		for(i = 1; i <= m; i++){
			if(i != start && path[i] == -1 && mmap[t][i]) {
				q.push(i);
				path[i] = t;
			}
		}
		if (path[eend] != -1)
		{
			break;
		}
	}
	int flowincrease = 1000000;
	for (size_t i = eend; i != start; i = path[i])
	{
		if (path[i] == -1)
		{
			return -1;
		}
		else
		{
			int temp = path[i];
			flowincrease = (flowincrease < mmap[temp][i]) ? flowincrease : mmap[temp][i];
		}
	}
	if( path[eend] == -1)
		return -1;
	return flowincrease;                   //一次遍历之后的流量增量
}

int Edmonds_Karp(){
	int max_flow = 0, step, now, pre;
	while( true ) {
		step = bfs();
		if (step == -1) break;		//找不到增路径时退出
		max_flow += step;
		now = eend;
		while ( now != start) {
			pre = path[now];
			mmap[pre][now] -= step;      //更新正向边的实际容量
			mmap[now][pre] += step;      //添加反向边
			now = pre;
		}
	}
	return max_flow;
}

int main() {
	//用邻接矩阵表示图的邻接关系，初始化所有权重为0
	memset(mmap, 0, sizeof(mmap));

	int u,v,w;
	cin >> m >> n >> start >> eend;
	for (int i = 0; i < n; i++)
	{
		cin >> u >> v >> w;
		mmap[u][v] = w;
	}

	//计算图的最大流
	int maxflow = Edmonds_Karp();			//计算最大流
	cout << maxflow << endl;
	return 0;
}

