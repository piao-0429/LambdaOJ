#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<memory.h>
using namespace std;
const int N_max = 30005;
const int M_max = 400005;
const int inf = 0x3f3f3f3f;
bool visit[N_max];
int dist[N_max];
vector<int> path_before[N_max];
typedef pair<int, int> Pair;
typedef struct Edge
{
	int toward, weight;
}Edge;
vector<Edge> graph[N_max];
vector<int> p;
void DJ(int start, int end)
{
	priority_queue<Pair, vector<Pair>, greater<Pair>> q;
	q.push(Pair(0, start));
	while (!q.empty() && !visit[end])
	{
		Pair tmp_p = q.top();
		q.pop();
		int tmp_v = tmp_p.second;
		if (visit[tmp_v]) continue;
		visit[tmp_v] = true;
		Edge tmp_e;
		for (int i = 0; i < graph[tmp_v].size(); i++)
		{
			tmp_e = graph[tmp_v][i];
			if (!visit[tmp_e.toward])
			{
				if (dist[tmp_e.toward] == dist[tmp_v] + tmp_e.weight)
				{
					path_before[tmp_e.toward].push_back(tmp_v);
				}
				else if (dist[tmp_e.toward] > dist[tmp_v] + tmp_e.weight)
				{
					dist[tmp_e.toward] = dist[tmp_v] + tmp_e.weight;
					path_before[tmp_e.toward].clear();
					path_before[tmp_e.toward].push_back(tmp_v);
					q.push(Pair(dist[tmp_e.toward], tmp_e.toward));
				}
			}
		}
	}
}
void del_edge(int v_1,int v_2)
{
	for (int i = 0; i < graph[v_1].size(); i++)
	{
		if (graph[v_1][i].toward == v_2)
		{
			graph[v_1].erase(graph[v_1].begin() + i);
		}
	}
	for (int i = 0; i < graph[v_2].size(); i++)
	{
		if (graph[v_2][i].toward == v_1)
		{
			graph[v_2].erase(graph[v_2].begin() + i);
		}
	}
}
void del_path(int start, int end)
{
	if (start == end) return;
	else
	{
		for (int i = 0; i < path_before[end].size(); i++)
		{
			int v_1 = end;
			int v_2 = path_before[end][i];
			del_edge(v_1, v_2);
			del_path(start, path_before[end][i]);
		}
	}
}
int main()
{
	std::ios::sync_with_stdio(false);
	int N, M, S, D;
	int v_1, v_2, w, v;
	Edge tmp_1, tmp_2;
	for (int i = 0; i < N_max; i++)
	{
		visit[i] = false;
		dist[i] = inf;
	}
	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		cin >> v_1 >> v_2 >> w;
		tmp_1.toward = v_2;
		tmp_2.toward = v_1;
		tmp_1.weight = tmp_2.weight = w;
		graph[v_1].push_back(tmp_1);
		graph[v_2].push_back(tmp_2);
	}
	cin >> S >> D;
	dist[S] = 0;
	DJ(S, D);
	cout << "start" << endl;
	v = D;
	while (path_before[v][0] != S)
	{
		p.push_back(v);
		v = path_before[v][0];
	}
	p.push_back(v);
	p.push_back(S);
	reverse(p.begin(), p.end());
	for (int i = 0; i < p.size(); i++)
	{
		cout << p[i] << endl;
	}
	cout << "end" << endl;
	cout << dist[D] << endl;
	del_path(S, D);
	for (int i = 0; i < N; i++)
	{
		path_before[i].clear();
	}
	for (int i = 0; i < N_max; i++)
	{
		visit[i] = false;
		dist[i] = inf;
    }
	dist[S] = 0;
	DJ(S, D);
	p.clear();
	if (dist[D] != inf)
	{
		cout << "start" << endl;
		v = D;
		while (path_before[v][0] != S)
		{
			p.push_back(v);
			v = path_before[v][0];
		}
		p.push_back(v);
		p.push_back(S);
		reverse(p.begin(), p.end());
		for (int i = 0; i < p.size(); i++)
		{
			cout << p[i] << endl;
		}
		cout << "end" << endl;
		cout << dist[D] << endl;
	}
	return 0;
}