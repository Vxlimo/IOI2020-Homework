#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <vector>
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
const int N = 2e5;

int l, r, n, m, s, t;
struct Edge {
	int	to, next, oppo;
	int	done, maxx;
} edge[(N << 3) + 1];
int tot, start[N + 1], cur[N + 1];
queue<int> q;
int vis[N + 1], dep[N + 1];
int to[N + 1], viss[N + 1];
vector<int> in[N + 1];
int ans;
int ansa[N + 1], ansb[N + 1];

inline void addedge(int u, int v, int flow)
{
	edge[++tot] = Edge{ v, start[u], tot + 1, 0, flow };
	start[u] = tot;
	edge[++tot] = Edge{ u, start[v], tot - 1, 0, 0 };
	start[v] = tot;
	return;
}
inline bool bfs()
{
	for (int i = 0; i <= (n << 1) - 1; i++)
		vis[i] = dep[i] = 0;
	q.push(s);
	dep[s] = vis[s] = 1;
	while (q.size()) {
		int u = q.front();
		q.pop();
		for (int i = start[u]; i; i = edge[i].next) {
			int v = edge[i].to;
			if (!vis[v] && edge[i].done < edge[i].maxx) {
				dep[v] = dep[u] + 1;
				vis[v] = 1;
				q.push(v);
			}
		}
	}
	return dep[t];
}
inline int dfs(int u, int flow)
{
	if (u == t || !flow)
		return flow;
	int val = 0;
	for (int &i = cur[u]; i; i = edge[i].next) {
		int v = edge[i].to;
		if (dep[v] == dep[u] + 1) {
			int w = dfs(v, min(flow, edge[i].maxx - edge[i].done));
			if (w > 0) {
				edge[i].done += w;
				edge[edge[i].oppo].done -= w;
				val += w;
				flow -= w;
				if (!flow)
					break;
			}
		}
	}
	return val;
}
inline void dinic()
{
	while (bfs()) {
		for (int i = 0; i <= (n << 1) - 1; i++)
			cur[i] = start[i];
		ans += dfs(s, 2147483647);
	}
	return;
}
inline int solve()
{
	for (int i = 1; i < n; i++) {
		for (int j = start[i]; j; j = edge[j].next) {
			if (edge[j].to)
				if (edge[j].done)
					to[i] = edge[j].to - n + 1;
		}
	}
	q.push(n);
	int link = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = 0; i < in[u].size(); i++) {
			int v = in[u][i];
			if (viss[v])
				continue;
			link++;
			ansa[v] = u;
			ansb[v] = to[v];
			q.push(to[v]);
			viss[v] = 1;
		}
	}
	return link;
}
int main()
{
	n = read();
	s = 0;
	t = (n << 1) - 1;
	for (int i = 1; i < n; i++) {
		int k = read();
		for (int j = 1; j <= k; j++) {
			int x = read();
			if (x != n)
				addedge(i, n + x - 1, 1e9);
			in[x].push_back(i);
		}
	}
	for (int i = 1; i < n; i++)
		addedge(0, i, 1);
	for (int i = 1; i <= n; i++)
		addedge(i + n - 1, (n << 1) - 1, 1);

	dinic();

	if (ans < n - 1) {
		printf("-1\n");
		return 0;
	}
	if (solve() < n - 1) {
		printf("-1");
		return 0;
	}
	for (int i = 1; i < n; i++)
		printf("%d %d\n", ansa[i], ansb[i]);
	return 0;
}
