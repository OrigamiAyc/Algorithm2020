// Program to find Dijkstra's shortest path using
// priority_queue in STL
#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <numeric>
#include <algorithm>
using namespace std;
#define INF 100000

typedef pair<int, int> iPair;

// This class represents a directed graph using adjacency list representation
class Graph
{
	int V;
	list<pair<int, int> > *adj; // This simply stores directed edges and their weights

public:
	Graph(int V);
	void addEdge(int u, int v, int w);
	void shortestPath(int s, int d);
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<iPair>[V];
}

void Graph::addEdge(int u, int v, int w)
{
	adj[u].push_back(make_pair(v, w));
}

// Prints shortest paths from src to all other vertices
void Graph::shortestPath(int src, int des)
{
	// Refer below link for details of this syntax
	// https://www.geeksforgeeks.org/implement-min-heap-using-stl/
	// To store the vertexes that has been found out their shortest path
	// item structure is <shortestDist, vertexSeq>
	// Act like a BFS, when a vertex's neighbour is pushed into the queue, it will be poped out
	// Since the push action is done only when need to udate dist, the BFS won't be forever due to circles
	priority_queue<iPair, vector<iPair>, greater<iPair> > BFSQ;
	vector<int> dist(V, INF);
	BFSQ.push(make_pair(0, src));
	dist[src] = 0;

	while (!BFSQ.empty())
	{
		int u = BFSQ.top().second;
		BFSQ.pop();

		// 'i' is used to get all adjacent vertices of a vertex
		list<pair<int, int> >::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			int v = (*i).first;
			int weight = (*i).second;

			// If there is shorted path to v through u.
			if (dist[v] > dist[u] + weight)
			{
				// Updating distance of v
				dist[v] = dist[u] + weight;
				BFSQ.push(make_pair(dist[v], v));
			}
		}
	}
	cout << dist[des] << endl;
}

int main()
{
	int V, E, S, T;
	cin >> V >> E >> S >> T;
	Graph g(V);

	for (size_t i = 0; i < E; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		g.addEdge(u, v, w);
	}

	g.shortestPath(S, T);

	return 0;
}
