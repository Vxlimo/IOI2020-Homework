#include <iostream>
#include <cstdlib>
#include <cstdio>
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

int n, m, q;
struct Graph {
	struct Edge {
		int from, to, next;
	} edge[N * 2 + 2];
	int start[N + 1], tot = 1;
	inline void addedge(int u, int v)
	{
		edge[++tot] = { u, v, start[u] };
		start[u] = tot;
		edge[++tot] = { v, u, start[v] };
		start[v] = tot;
		return;
	}
	int	dfn[N + 1], low[N + 1], cnt;
	int	st[N + 1], top;
	int	belong[N + 1], w;
	inline void tarjan(int u, int fa)
	{
		dfn[u] = low[u] = ++cnt;
		st[++top] = u;
		for (int i = start[u]; i; i = edge[i].next) {
			int v = edge[i].to;
			if (i / 2 != fa / 2) {
				if (!dfn[v]) {
					tarjan(v, i);
					low[u] = min(low[u], low[v]);
				} else {
					low[u] = min(low[u], dfn[v]);
				}
			}
		}
		if (dfn[u] == low[u]) {
			w++;
			while (st[top] != u)
				belong[st[top--]] = w;
			belong[st[top--]] = w;
		}
		return;
	}
	int fa[N + 1][18], dep[N + 1];
	inline void dfs(int u)
	{
		dep[u] = dep[fa[u][0]] + 1;
		for (int i = 1; i <= 17; i++)
			fa[u][i] = fa[fa[u][i - 1]][i - 1];
		for (int i = start[u]; i; i = edge[i].next) {
			int v = edge[i].to;
			if (v != fa[u][0]) {
				fa[v][0] = u;
				dfs(v);
			}
		}
		return;
	}
	inline int lca(int u, int v)
	{
		if (dep[u] > dep[v])
			swap(u, v);
		for (int i = 17; i >= 0; i--)
			if (dep[fa[v][i]] >= dep[u])
				v = fa[v][i];
		if (u == v)
			return u;
		for (int i = 17; i >= 0; i--) {
			if (fa[u][i] != fa[v][i]) {
				u = fa[u][i];
				v = fa[v][i];
			}
		}
		return fa[u][0];
	}
	int up[N + 1], down[N + 1];
	inline bool check(int u)
	{
		for (int i = start[u]; i; i = edge[i].next) {
			int v = edge[i].to;
			if (v != fa[u][0]) {
				if (!check(v))
					return false;
				up[u] += up[v];
				down[u] += down[v];
			}
		}
		if (up[u] && down[u])
			return false;
		return true;
	}
} A, B;

int main()
{
	n = read();
	m = read();
	q = read();
	for (int i = 1; i <= m; i++)
		A.addedge(read(), read());

	for (int i = 1; i <= n; i++)
		if (!A.belong[i])
			A.tarjan(i, 0);
	for (int i = 1; i <= A.tot; i += 2)
		if (A.belong[A.edge[i].from] != A.belong[A.edge[i].to])
			B.addedge(A.belong[A.edge[i].from], A.belong[A.edge[i].to]);
	for (int i = 1; i <= A.w; i++)
		if (!B.dep[i])
			B.dfs(i);
	for (int i = 1; i <= q; i++) {
		int u = A.belong[read()], v = A.belong[read()], l = B.lca(u, v);
		B.up[u]++;
		B.up[l]--;
		B.down[v]++;
		B.down[l]--;
	}

	for (int i = 1; i <= A.w; i++) {
		if (B.fa[i][0] == 0) {
			if (!B.check(i)) {
				printf("No\n");
				return 0;
			}
		}
	}
	printf("Yes\n");
	return 0;
}
