#include <iostream>
#include <vector>
#include <list>
#include <queue>
using namespace std;
#define INF 2147483647

class Graph {
	int N;

	list<pair<int, int> >* adjacency;

public:
	Graph(int N);

	void AddEdge(int current, int N, int w);

	int Dijkstra(int from, int to);
};

Graph::Graph(int N): N(N)
{
	adjacency = new list<pair<int, int> >[N];
}

void Graph::AddEdge(int from, int to, int w)
{
	adjacency[from].push_back({ to, w });
	adjacency[to].push_back({ from, w });
}

int Graph::Dijkstra(int from, int to)
{
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

	vector<int> dist(N, INF);

	pq.push({ 0, from });
	dist[from] = 0;

	while (!pq.empty()) {

		int current = pq.top().second;
		pq.pop();

		for (auto i = adjacency[current].begin(); i != adjacency[current].end(); ++i) {
			if (dist[(*i).first] > dist[current] + (*i).second) {
				dist[(*i).first] = dist[current] + (*i).second;
				pq.push({ dist[(*i).first], (*i).first });
			}
		}
	}
	return dist[to];
}

int main()
{
	int n, k, a, b, w;
	cin >> n;
	Graph graph(n);
	cin >> k;
	for (int i = 0; i < k; ++i) {
		cin >> a >> b >> w;
		graph.AddEdge(a, b, w);
	}
	cin >> a >> b;
	cout << graph.Dijkstra(a, b);
	return 0;
}
