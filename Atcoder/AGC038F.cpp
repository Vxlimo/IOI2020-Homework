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
const int N = 2e5 + 1;

int n, s, t;
int a[N + 1], b[N + 1];
int id[3][N + 1], cnt;
struct Edge {
	int	to, next, oppo;
	int	done, maxx;
} edge[(N << 3) + 1];
int tot, start[N + 1], cur[N + 1];
queue<int> q;
int vis[N + 1], dep[N + 1];
int ans, num;

inline void add(int u, int v, int flow)
{
	edge[++tot] = Edge{ v, start[u], tot + 1, 0, flow };
	start[u] = tot;
	edge[++tot] = Edge{ u, start[v], tot - 1, 0, 0 };
	start[v] = tot;
	return;
}
inline bool bfs()
{
	for (int i = s; i <= t; i++)
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
		for (int i = s; i <= t; i++)
			cur[i] = start[i];
		ans += dfs(s, 2147483647);
	}
	return;
}
inline void number(int now, int opt)
{
	if (id[opt][now])
		return;
	id[opt][now] = cnt;
	if (opt == 1)
		number(a[now] + 1, opt);
	else
		number(b[now] + 1, opt);
	return;
}
int main()
{
	n = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	for (int i = 1; i <= n; i++)
		b[i] = read();
	for (int i = 1; i <= n; i++) {
		if (!id[1][i]) {
			cnt++;
			number(i, 1);
		}
	}
	for (int i = 1; i <= n; i++) {
		if (!id[2][i]) {
			cnt++;
			number(i, 2);
		}
	}
	s = 0;
	t = ++cnt;
	for (int i = 1; i <= n; i++) {
		if (a[i] == b[i]) {
			if (a[i] == i - 1) {
				num++;
			} else {
				add(id[1][i], id[2][i], 1);
				add(id[2][i], id[1][i], 1);
			}
		} else {
			if (a[i] != i - 1 && b[i] == i - 1)
				add(s, id[1][i], 1);
			if (a[i] == i - 1 && b[i] != i - 1)
				add(id[2][i], t, 1);
			if (a[i] != i - 1 && b[i] != i - 1)
				add(id[2][i], id[1][i], 1);
		}
	}

	dinic();

	printf("%d\n", n - num - ans);
	return 0;
}
