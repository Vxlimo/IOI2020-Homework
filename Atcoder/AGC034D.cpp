#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <cstring>
#define ll long long
using namespace std;
inline int read()
{
	int f = 1, x = 0;
	char ch;

	do{
		ch = getchar();
		if (ch == '-')
			f = -1;
	}while(ch < '0' || ch > '9');
	do{
		x = x * 10 + ch - '0';
		ch = getchar();
	}while(ch >= '0' && ch <= '9');
	return f * x;
}
const int M = 1e5;
const int N = 5e3;

int n, s = 0, t = 9, cnt = 9;
struct Edge {
	int to, flow, maxx, cost, next, oppo;
} edge[M + 1];
int start[N + 1], cur[N + 1], tot;
queue<int> q;
int vis[N + 1];
ll dis[N + 1];
int maxflow;
ll maxcost;

inline void addedge(int u, int v, int flow, int cost)
{
	edge[++tot] = Edge{ v, 0, flow, cost, start[u], tot + 1 };
	start[u] = tot;
	edge[++tot] = Edge{ u, 0, 0, -cost, start[v], tot - 1 };
	start[v] = tot;
	return;
}
inline bool spfa()
{
	for (int i = 0; i <= N; i++)
		dis[i] = -1e18;
	q.push(s);
	dis[s] = 0;
	vis[s] = 1;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		vis[u] = 0;
		for (int i = start[u]; i; i = edge[i].next) {
			int v = edge[i].to;
			if (edge[i].flow<edge[i].maxx && dis[u] + edge[i].cost>dis[v]) {
				dis[v] = dis[u] + edge[i].cost;
				if (!vis[v]) {
					vis[v] = 1;
					q.push(v);
				}
			}
		}
	}
	return dis[t] != -1e18;
}
inline int dfs(int u, int flow)
{
	if (u == t || !flow)
		return flow;
	int totflow = 0;
	vis[u] = 1;
	for (int &i = cur[u]; i; i = edge[i].next) {
		int v = edge[i].to;
		if (!vis[v] && edge[i].flow < edge[i].maxx && dis[u] + edge[i].cost == dis[v]) {
			int w = dfs(v, min(flow, edge[i].maxx - edge[i].flow));
			if (w > 0) {
				edge[i].flow += w;
				edge[edge[i].oppo].flow -= w;
				totflow += w;
				flow -= w;
				maxcost += 1ll * edge[i].cost * w;
				if (!flow)
					break;
			}
		}
	}
	vis[u] = 0;
	return totflow;
}
inline void mcmf()
{
	while (spfa()) {
		memcpy(cur, start, 4 * (N + 1));
		while (true) {
			int w = dfs(s, 1e9);
			if (!w)
				break;
			maxflow += w;
		}
	}
	return;
}
int main()
{
	n = read();
	for (int i = 1; i <= n; i++) {
		int x = read(), y = read(), z = read();
		addedge(s, ++cnt, z, 0);
		addedge(cnt, 1, 1e9, x + y);
		addedge(cnt, 2, 1e9, x - y);
		addedge(cnt, 3, 1e9, y - x);
		addedge(cnt, 4, 1e9, -x - y);
	}
	for (int i = 1; i <= n; i++) {
		int x = read(), y = read(), z = read();
		addedge(++cnt, t, z, 0);
		addedge(5, cnt, 1e9, x + y);
		addedge(6, cnt, 1e9, x - y);
		addedge(7, cnt, 1e9, y - x);
		addedge(8, cnt, 1e9, -x - y);
	}
	addedge(1, 8, 1e9, 0);
	addedge(2, 7, 1e9, 0);
	addedge(3, 6, 1e9, 0);
	addedge(4, 5, 1e9, 0);

	mcmf();

	printf("%lld\n", maxcost);
	return 0;
}
