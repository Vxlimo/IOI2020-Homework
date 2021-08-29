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
const int N = 1e5;
const int M = 5e5;

int n, m;
struct Edge {
	int to, next, vis;
} edge[M * 2 + 1];
int start[N + 1], tot = 1, d[N + 1];
int st[M + 1], top;

inline void addedge(int u, int v)
{
	edge[++tot] = { v, start[u], 0 };
	start[u] = tot;
	d[u]++;
	edge[++tot] = { u, start[v], 0 };
	start[v] = tot;
	d[v]++;
	return;
}
inline void dfs(int u)
{
	for (int &i = start[u]; i; i = edge[i].next) {
		if (edge[i].vis)
			continue;
		int v = edge[i].to;
		edge[i].vis = edge[i ^ 1].vis = 1;
		dfs(v);
	}
	st[++top] = u;
	return;
}
int main()
{
	n = read();
	m = read();
	for (int i = 1; i <= m; i++)
		addedge(read(), read());
	int la = 0;

	for (int i = 1; i <= n; i++) {
		if (d[i] & 1) {
			if (la) {
				addedge(la, i);
				la = 0;
			} else {
				la = i;
			}
		}
	}
	if ((tot >> 1) & 1)
		addedge(1, 1);

	dfs(1);

	printf("%d\n", tot >> 1);
	for (int i = 1, j = 1; i < top; i++, j ^= 1) {
		if (j)
			printf("%d %d\n", st[i], st[i + 1]);
		else
			printf("%d %d\n", st[i + 1], st[i]);
	}
	return 0;
}
