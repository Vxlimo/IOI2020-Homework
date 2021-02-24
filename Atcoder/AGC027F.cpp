#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <queue>
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
const int N = 50;

int tt;
int n;
struct Edge {
	int from, to, next;
};
struct Tree {
	Edge	edge[(N << 1) + 1];
	int	start[N + 1], tot, fa[N + 1], d[N + 1];
	int	connect[N + 1][N + 1];
	inline void init()
	{
		for (int i = 1; i <= n; i++) {
			start[i] = d[i] = 0;
			for (int j = 1; j <= n; j++)
				connect[i][j] = 0;
		}
		tot = 0;
		return;
	}
	inline void addedge(int u, int v)
	{
		edge[++tot] = { u, v, start[u] };
		start[u] = tot;
		d[u]++;
		edge[++tot] = { v, u, start[v] };
		start[v] = tot;
		d[v]++;
		connect[u][v] = connect[v][u] = 1;
		return;
	}
	inline void dfs(int u)
	{
		for (int i = start[u]; i; i = edge[i].next) {
			int v = edge[i].to;
			if (v != fa[u]) {
				fa[v] = u;
				dfs(v);
			}
		}
		return;
	}
} A, B, C;
struct Graph {
	Edge	edge[(N << 1) + 1];
	int	start[N + 1], ind[N + 1], tot;
	int	vis[N + 1];
	inline void init()
	{
		for (int i = 1; i <= n; i++)
			start[i] = vis[i] = ind[i] = 0;
		tot = 0;
		return;
	}
	inline void addedge(int u, int v)
	{
		edge[++tot] = { u, v, start[u] };
		start[u] = tot;
		ind[v]++;
		return;
	}
	inline void bfs()
	{
		queue<int> q;

		for (int i = 1; i <= n; i++)
			if (!ind[i])
				q.push(i);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			vis[u] = 1;
			for (int i = start[u]; i; i = edge[i].next) {
				int v = edge[i].to;
				if (!vis[v]) {
					ind[v]--;
					if (!ind[v])
						q.push(v);
				}
			}
		}
		return;
	}
} G;
int need[N + 1];
int ans;

inline int calc(int root)
{
	int sum = 0;

	G.init();
	A.fa[root] = B.fa[root] = root;
	A.dfs(root);
	B.dfs(root);
	for (int i = 1; i <= n; i++)
		need[i] = A.fa[i] != B.fa[i];
	for (int i = 1; i <= n; i++) {
		if (i == root)
			continue;
		if (!need[i] && A.fa[i] && need[A.fa[i]])
			return 1e9;
		if (!need[i])
			continue;
		if (B.fa[i] && need[B.fa[i]])
			G.addedge(B.fa[i], i);
		if (A.fa[i] && need[A.fa[i]])
			G.addedge(i, A.fa[i]);
		sum++;
	}
	G.bfs();
	for (int i = 1; i <= n; i++)
		if (need[i] && !G.vis[i])
			return 1e9;
	return sum;
}
int main()
{
	tt = read();

	while (tt--) {
		ans = 1e9;
		C.init();
		B.init();
		n = read();
		for (int i = 1; i < n; i++) {
			int u = read(), v = read();
			C.addedge(u, v);
		}
		for (int i = 1; i < n; i++) {
			int u = read(), v = read();
			B.addedge(u, v);
		}
		for (int i = 1; i <= n; i++) {
			if (C.d[i] == 1) {
				for (int j = 1; j <= n; j++) {
					if (i == j)
						continue;
					A.init();
					for (int k = 1; k <= C.tot; k += 2)
						if (C.edge[k].from != i && C.edge[k].to != i)
							A.addedge(C.edge[k].from, C.edge[k].to);
					A.addedge(i, j);
					ans = min(ans, calc(i) + (C.connect[i][j] ^ 1));
				}
			}
		}
		printf("%d\n", ans == 1e9?-1:ans);
	}

	return 0;
}
