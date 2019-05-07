#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int BFS(vector<vector<int>> graph, int from, int to) {
  vector<int> dist(graph.size(), 50000);
	vector<int> path(graph.size(), 0);
	vector<int8_t> visited(graph.size(), 0);
	queue<int> q;
	vector<int> dist(graph.size(), 50000);
	vector<int> path(graph.size(), 0);
	path[from] = 1;
	for (auto i : graph[from]) {
		path[i] = 1;
	}
	q.push(from);
	dist[from] = 0;

	while (!q.empty()) {
		int v = q.front();
		q.pop();
		visited[v] = 1;
		for (auto i : graph[v]) {
			if (dist[v] + 1 < dist[i]) {
				dist[i] = dist[v] + 1;
				path[i] = path[v];
			}
			else if ((dist[v] + 1) == dist[i]) {
				path[i] += path[v];
			}
			if (!visited[i]) {
				q.push(i);
				visited[i] = 1;
			}
		}
	}
	return path[to];
}
int main() {
	int n, a, b;
	cin >> n;
	vector<vector<int>> graph(n);
  cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> a >> b;
		graph[a].emplace_back(b);
		graph[b].emplace_back(a);
	}
	cin >> a >> b;
	cout << BFS(graph, a, b);
	return 0;
}
