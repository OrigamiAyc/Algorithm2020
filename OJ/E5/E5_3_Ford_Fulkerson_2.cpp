// C++ program for implementation of Ford Fulkerson algorithm
#include <iostream>
#include <climits>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define min(a, b) ((a) < (b)) ? a : b

// Number of vertices in given graph
int V, E, S, T;
vector<vector<int> > Graph;

bool bfs(int s, int t, int parent[])
{
	// Create a visited array and mark all vertices as not visited
	bool visited[V];
	memset(visited, 0, sizeof(visited));

	// Create a queue, enqueue source vertex and mark source vertex as visited
	queue<int> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	// Standard BFS Loop
	int u;
	while (!q.empty())
	{
		// edge: u -> v
		u = q.front(); // head point u
		q.pop();
		for (int v = 0; v < V; ++v) // tail point v
		{
			if (!visited[v] && Graph[u][v] > 0) // find one linked vertex
			{
				q.push(v);
				parent[v] = u; // find pre point
				visited[v] = true;
			}
		}
	}

	// If we reached sink in BFS starting from source, then return true, else false
	return visited[t] == true;
}

// Returns the maximum flow from s to t in the given graph
int fordFulkerson(int s, int t)
{
	int u, v;

	int parent[V];
	int max_flow = 0;

	// Augment the flow while tere is path from source to sink
	while (bfs(s, t, parent))
	{
		// edge: u -> v
		int path_flow = INT_MAX;
		for (v = t; v != s; v = parent[v])
		{
			// find the minimum flow
			u = parent[v];
			path_flow = min(path_flow, Graph[u][v]);
		}

		// update residual capacities of the edges and reverse edges along the path
		for (v = t; v != s; v = parent[v])
		{
			u = parent[v];
			Graph[u][v] -= path_flow;
			Graph[v][u] += path_flow; // assuming v->u weight is add path_flow
		}

		// Add path flow to overall flow
		max_flow += path_flow;
	}

	return max_flow;
}

int main()
{
	cin >> V >> E >> S >> T;
	Graph.resize(V);
	for (size_t i = 0; i < V; i++)
	{
		Graph[i].resize(V);
	}

	int u, v, w;
	for (size_t i = 0; i < E; i++)
	{
		cin >> u >> v >> w;
		Graph[u][v] = w;
	}

	cout << fordFulkerson(S, T) << endl;

	return 0;
}
