#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cstring>
#include <algorithm>
using namespace std;

#define _VECTOREDGE vector<edgeMap>
#define INF 10000
#define NIL -1

typedef struct
{
	int destination;
	int edgeWeight;
} edgeMap;

struct Distance
{
	int vertex;
	int dis;
	// bool operator>(const Distance &a) const {
	// 	return dis > a.dis;
	// };
};

const int maxVertex = 1e5;
const int maxEdge = 1e6;

// vector<int> dist; // to store the min path length from this point to source
// vector<int> prev; // to store the father on the min tree

class Graph
{
private:
	int Vnum, Enum;
	vector<map<int, int> > vertex; // to store the vertexes, along with the edges that sources from each vertex
	// vector<_VECTOREDGE> vertex; // to store the vertexes, along with the edges that sources from each vertex
	vector<int> dist; // to store the min path length from this point to source
	vector<int> prev; // to store the father on the min tree
	// priority_queue<Distance> unvisitedQ;
public:
	Graph(int V, int E);
	void insertEdge(int src, int des, int len);
	int findDistance(int src, int des);
	void initializeSingleSource(int src);
	void relax(int halfV, int desV);
	void dijkstra(int src, int dis);
	~Graph();
};

Graph::Graph(int vertex, int edge)
{
	this->Vnum = vertex;
	this->Enum = edge;
	this->vertex.resize(vertex);
}

void Graph::insertEdge(int source, int destination, int length)
{
	auto iter = this->vertex[source - 1].find(destination);
	if (iter != this->vertex[source - 1].end())
	{
		/**
		 * there is already a record in the graph
		 * choose the shortest path between two vertexes
		 **/
		int originalLength = iter->second;
		if (originalLength > length)
		{
			this->vertex[source - 1][destination] = length;
		}
	}
	else
	{
		this->vertex[source - 1].insert(pair<int, int>(destination, length));
	}
	return;
	// this->vertex[source - 1].push_back((edgeMap){destination, length});
}

int Graph::findDistance(int src, int des)
{
	if (this->vertex[src - 1].count(des))
	{
		return this->vertex[src - 1][des];
	}
	else
	{
		return INF;
	}
}

void Graph::initializeSingleSource(int src)
{
	this->dist.resize(this->Vnum);
	this->prev.resize(this->Vnum);
	for (size_t i = 0; i < this->Vnum; i++)
	{
		this->dist[i] = INF;
		this->prev[i] = NIL;
		// if (i + 1 != src)
		// {
		// 	this->unvisitedQ.push((Distance){i + 1, dist[i]});
		// }
	}
	this->dist[src - 1] = 0;
}

void Graph::relax(int u, int v)
{
	int weight = this->findDistance(u, v);
	if (this->dist[v - 1] > this->dist[u - 1] + weight)
	{
		this->dist[v - 1] = this->dist[u - 1] + weight;
		this->prev[v - 1] = u;
	}
}

void Graph::dijkstra(int src, int dis)
{
	this->initializeSingleSource(src);
	set<int> visitedS;
	bool unvisitedS[this->Vnum];
	memset(unvisitedS, 1, sizeof(unvisitedS));
	unvisitedS[src - 1] = false;
	visitedS.insert(src);
	while (visitedS.size() != this->Vnum)
	{
		// auto u = this->unvisitedQ.top();
		// this->unvisitedQ.pop();
		/**
		 * To find out the nearest vertex in the unvisited set
		 **/
		int u = INF;
		for (size_t i = 0; i < this->Vnum; i++)
		{
			if (unvisitedS[i] && this->dist[i] < u)
			{
				u = this->dist[i];
			}
		}

		visitedS.insert(u); // .vertex);
		for (auto adj : this->vertex[u - 1])
		{
			this->relax(adj.first, u);
		}
		// visitedS[u.vertex - 1] = true;
	}
	cout << this->dist[dis - 1] << endl;
}

Graph::~Graph()
{
}

// class Dijkstra : public Graph
// {
// private:
// 	vector<int> dist; // to store the min path length from this point to source
// 	vector<int> prev; // to store the father on the min tree
// public:
// 	void initializeSingleSource(int src);
// };

int main(int argc, char const *argv[])
{
	int V, E, S, T;
	cin >> V >> E >> S >> T;
	Graph g(V, E);
	cout << "create a graph" << endl;

	for (size_t i = 0; i < E; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		g.insertEdge(u, v, w);
	}

	g.dijkstra(S, T);

	return 0;
}
