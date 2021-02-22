#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;
inline ll read()
{
	ll f = 1, x = 0;
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
const int N = 1e5;

int n, q;
ll l;
struct Edge {
	int to, next, w;
} edge[(N << 1) + 1];
int start[N + 1], d[N + 1], tot;
ll dis[N + 1], dis1[N + 1];
int fa[N + 1];
int opt[N + 1];
namespace dsu
{
int f[N + 1], sz[N + 1], last[N + 1];
inline void init()
{
	for (int i = 1; i <= n; i++) {
		f[i] = i;
		sz[i] = last[i] = 1;
	}
	return;
}
inline int gfa(int x)
{
	if (f[x] != x)
		f[x] = gfa(f[x]);
	return f[x];
}
inline void merge(int x, int y)
{
	x = gfa(x);
	y = gfa(y);
	if (x == y)
		return;
	if (sz[x] < sz[y])
		swap(x, y);
	sz[x] += sz[y];
	last[x] += last[y];
	f[y] = x;
	return;
}
}
int ans;

inline void addedge(int u, int v, int w)
{
	edge[++tot] = { v, start[u], w };
	start[u] = tot;
	d[u]++;
	edge[++tot] = { u, start[v], w };
	start[v] = tot;
	d[v]++;
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
inline void dfs1(int u)
{
	for (int i = start[u]; i; i = edge[i].next) {
		int v = edge[i].to;
		if (v != fa[u]) {
			fa[v] = u;
			dfs1(v);
			if (dis[v] + edge[i].w > dis[u]) {
				dis1[u] = dis[u];
				dis[u] = dis[v] + edge[i].w;
			} else {
				if (dis[v] + edge[i].w > dis1[u])
					dis1[u] = dis[v] + edge[i].w;
			}
		}
	}
	return;
}
inline void dfs2(int u)
{
	for (int i = start[u]; i; i = edge[i].next) {
		int v = edge[i].to;
		if (v != fa[u]) {
			if (dis[v] + edge[i].w == dis[u]) {
				if (dis1[u] + edge[i].w > dis[v]) {
					dis1[v] = dis[v];
					dis[v] = dis1[u] + edge[i].w;
				} else {
					if (dis1[u] + edge[i].w > dis1[v])
						dis1[v] = dis1[u] + edge[i].w;
				}
			} else {
				if (dis[u] + edge[i].w > dis[v]) {
					dis1[v] = dis[v];
					dis[v] = dis[u] + edge[i].w;
				} else {
					if (dis[u] + edge[i].w > dis1[v])
						dis1[v] = dis[u] + edge[i].w;
				}
			}
			dfs2(v);
		}
	}
	return;
}
inline bool compare(int x, int y)
{
	return dis[x] > dis[y];
}
int main()
{
	n = read();
	for (int i = 1; i < n; i++) {
		int u = read(), v = read(), w = read();
		addedge(u, v, w);
	}
	for (int i = 1; i <= n; i++) {
		if (d[i] != 1) {
			dfs1(i);
			dfs2(i);
			break;
		}
	}
	for (int i = 1; i <= n; i++)
		opt[i] = i;
	sort(opt + 1, opt + n + 1, compare);
	fa[opt[n]] = 0;
	dfs(opt[n]);
	q = read();

	while (q--) {
		l = read();
		dsu::init();
		ans = 0;
		int maxx = 1;
		for (int i = 1; i <= n; i++) {
			int u = opt[i];
			for (int j = start[u]; j; j = edge[j].next) {
				int v = edge[j].to;
				if (v != fa[u])
					dsu::merge(u, v);
			}
			while (dis[opt[maxx]] > dis[u] + l)
				dsu::last[dsu::gfa(opt[maxx++])]--;
			ans = max(ans, dsu::last[dsu::gfa(u)]);
		}
		printf("%d\n", ans);
	}

	return 0;
}
