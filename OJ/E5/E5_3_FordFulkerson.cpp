#include <iostream>
#include <string.h>
#include <algorithm>
#include <queue>
#include <vector>
#define INF 0x3f3f3f3f
#define MAXN 5000
using namespace std;
int n, S, T;				  //节点数，源点，汇点
vector<vector<int> > capacity; //残存网络的邻接矩阵
queue<int> qu;				  //广搜队列
int pre[MAXN], flow[MAXN];	  //前驱数组；增广路径中的节点流
int find_augmenting_path(int s, int t)
{
	int index;
	size_t i;
	memset(pre, -1, n * sizeof(int));
	while (!qu.empty())
		qu.pop();
	flow[s] = INF; //源点的流为INF
	qu.push(s);
	while (!qu.empty())
	{
		index = qu.front();
		qu.pop();
		if (index == t)
			break; //找到了一条增广路径
		for (i = 0; i < n; ++i)
			if (i != s && capacity[index][i] > 0 && pre[i] == -1)
			{ //每个节点只遍历一次
				pre[i] = index;
				flow[i] = min(capacity[index][i], flow[index]);
				qu.push(i);
			}
	}
	if (pre[t] == -1)
		return 0;
	return flow[t];
}
int maxflow(int s, int t)
{
	int sumflow = 0, v, prenode;
	while (int increaseflow = find_augmenting_path(s, t))
	{
		v = t;
		while (v != s)
		{ //从汇点通过前驱数组向源点更新残存网络
			prenode = pre[v];
			capacity[prenode][v] -= increaseflow;
			capacity[v][prenode] += increaseflow;
			v = prenode;
		}
		sumflow += increaseflow;
	}
	return sumflow;
}
int main()
{
	size_t i, m; // 边数
	int s, t, c; // 每条边的起点、终点和权重
	cin >> n >> m >> S >> T;
	capacity.assign(n, vector<int>(n, 0));
	for (i = 0; i < m; ++i)
	{
		cin >> s >> t >> c;
		s--, t--;
		capacity[s][t] = c;
	}
	cout << maxflow(S - 1, T - 1) << endl;
	return 0;
}
