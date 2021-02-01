#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <cstring>
using namespace std;

#ifndef DEBUG
#define DEBUG false
#endif // !DEBUG

const int INF = 1000000;

class Flow
{
private:
	int Vnum, Enum;
	int start, end;
	vector<map<int, int> > transport;
	queue<int> unvisitedQ;
	int *path, *flow;

public:
	Flow(int V, int E, int src, int des);
	void insert(int src, int des, int wei);
	void reset();
	int bfs();
	int EdmondsKarp();
	~Flow();
};

Flow::Flow(int V, int E, int src, int des)
{
	this->Vnum = V;
	this->Enum = E;
	this->start = src - 1;
	this->end = des - 1;
	this->transport.resize(E);
	this->path = new int(V);
	this->flow = new int(V);
}

void Flow::insert(int src, int des, int wei)
{
	if (DEBUG)
	{
		cout << "in insert" << endl;
	}
	if (this->transport[src - 1].count(des - 1))
	{
		this->transport[src - 1][des - 1] += wei;
	}
	else
	{
		(this->transport[src - 1]).insert(pair<int, int>(des - 1, wei));
	}
}

void Flow::reset()
{
	// clear this queue, path, flow
	while (!(this->unvisitedQ.empty()))
	{
		this->unvisitedQ.pop();
	}
	// memset(this->path, -1, (sizeof(int) * this->Vnum));
	for (size_t i = 0; i < this->Vnum; i++)
	{
		this->path[i] = -1;
	}
	this->path[this->start] = this->start;
	this->flow[this->start] = INF;
}

int Flow::bfs()
{
	this->reset();
	this->unvisitedQ.push(this->start);
	while (!(this->unvisitedQ.empty()))
	{
		int temp = this->unvisitedQ.front();
		this->unvisitedQ.pop();
		if (temp == this->end)
		{
			break;
		}
		for (auto ita : this->transport[temp])//size_t i = 0; i < this->Vnum; i++)
		{
			int i = ita.first;
			if ((i != this->start) && (this->path[i] == -1))
			// when visiting a non-source, unvisited neighbour of queue top
			{
				// always choose the min flow capacity in the path
				this->flow[i] = (this->flow[temp] < ita.second) ? this->flow[temp] : ita.second;
				this->unvisitedQ.push(i);
				// record its pre
				this->path[i] = temp;
			}
		}
	}
	if (this->path[this->end] == -1)
	{
		return -1;
	}
	else
	{
		return this->flow[this->end];
	}
}

int Flow::EdmondsKarp()
{
	int maxFlow = 0;
	// every step's flow increase, des and src of every edge in the path of this step
	int step, des, src;
	while (true)
	{
		step = this->bfs();
		// cout << "bfs ok" << endl;
		if (step == -1)
		{
			break;
		}
		maxFlow += step;
		des = this->end;
		cout << des << endl;
		while (des != this->start)
		{
			src = this->path[des];
			cout << this->path[des] << endl;
			this->transport[src][des] -= step;
			cout << this->transport[src][des] << endl;
			if (this->transport[des].count(src))
			{
				this->transport[des][src] += step;
			}
			else
			{
				this->transport[des].insert(pair<int, int>(src, step));
			}
			des = src;
		}
	}
	return maxFlow;
}

Flow::~Flow()
{
	delete this->path;
	delete this->flow;
}

int main(int argc, char const *argv[])
{
	int N, M, S, T;
	cin >> N >> M >> S >> T;
	Flow factory(N, M, S, T);
	for (size_t i = 0; i < M; i++)
	{
		int s, t, w;
		cin >> s >> t >> w;
		factory.insert(s, t, w);
	}

	int maxFlow = factory.EdmondsKarp();
	cout << maxFlow << endl;
	return 0;
}
