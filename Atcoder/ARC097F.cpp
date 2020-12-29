#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <cstring>
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

int n;
struct Edge {
	int to, next;
} edge[(N << 1) + 1];
int start[N + 1], tot, root = 1;
int disapp[N + 1], d[N + 1], color[N + 1];
int dis1[N + 1], dis2[N + 1], w[N + 1];
queue<int> q;
int num, ans;

inline void addedge(int u, int v)
{
	edge[++tot] = { v, start[u] };
	start[u] = tot;
	d[u]++;
	edge[++tot] = { u, start[v] };
	start[v] = tot;
	d[v]++;
	return;
}
inline void bfs()
{
	for (int i = 1; i <= n; i++)
		if (d[i] <= 1 && color[i] == 1) {
			q.push(i);
			disapp[i] = 1;
		}
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = start[u]; i; i = edge[i].next) {
			int v = edge[i].to;
			d[v]--;
			if (d[v] <= 1 && !disapp[v] && color[v] == 1) {
				disapp[v] = 1;
				q.push(v);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		if (!disapp[i] && d[i] != 1) {
			root = i;
			break;
		}
	}
	return;
}
inline void dfs(int u, int fa)
{
	for (int i = start[u]; i; i = edge[i].next) {
		int v = edge[i].to;
		if (!disapp[v] && v != fa) {
			dfs(v, u);
			if (dis1[v] > dis1[u]) {
				dis2[u] = dis1[u];
				dis1[u] = dis1[v];
			} else
			if (dis1[v] > dis2[u]) {
				dis2[u] = dis1[v];
			}
		}
	}
	num = max(dis1[u] + dis2[u] + w[u], num);
	dis1[u] += w[u];
	return;
}
int main()
{
	n = read();
	for (int i = 1; i < n; i++)
		addedge(read(), read());
	string s;

	cin >> s;
	for (int i = 0; i < n; i++)
		color[i + 1] = s[i] == 'B';
	if (n == 0) {
		printf("0\n");
		return 0;
	}
	if (n == 1) {
		printf("%d\n", color[1] == 0);
		return 0;
	}

	bfs();
	if (!root) {
		printf("0\n");
		return 0;
	}
	if (d[root] == 0) {
		printf("%d\n", color[root] == 0);
		return 0;
	}
	for (int i = 1; i <= n; i++) {
		if (!disapp[i]) {
			w[i] = ((d[i] & 1) ^ (color[i] & 1)) ^ 1;
			ans += d[i] + w[i];
		}
	}
	dfs(root, 0);

	printf("%d\n", ans - 2 * num);
	return 0;
}
