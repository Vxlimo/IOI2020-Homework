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
const int N = 2e3;

int n;
int had[N + 1];
struct Edge {
	int to, next;
} edge[(N << 1) + 1];
int start[N + 1], tot;
int f[N + 1], sum[N + 1], val[N + 1];
int ans = 1e9;

inline void addedge(int u, int v)
{
	edge[++tot] = Edge{ v, start[u] };
	start[u] = tot;
	edge[++tot] = Edge{ u, start[v] };
	start[v] = tot;
	return;
}
inline void dfs(int u, int fa)
{
	val[u] = had[u];
	sum[u] = 0;
	int maxx = 0;
	for (int i = start[u]; i; i = edge[i].next) {
		int v = edge[i].to;
		if (v != fa) {
			dfs(v, u);
			val[u] += val[v];
			sum[v] += val[v];
			sum[u] += sum[v];
			if (sum[v] > sum[maxx])
				maxx = v;
		}
	}
	if (!maxx) {
		f[u] = 0;
		return;
	}
	if (sum[u] - sum[maxx] >= sum[maxx])
		f[u] = sum[u] / 2;
	else
		f[u] = sum[u] - sum[maxx] + min(f[maxx], ((sum[maxx] << 1) - sum[u]) / 2);
	return;
}
int main()
{
	n = read();
	string s;
	cin >> s;
	for (int i = 1; i <= n; i++)
		had[i] = s[i - 1] - '0';
	for (int i = 1; i < n; i++) {
		int u = read(), v = read();
		addedge(u, v);
	}

	for (int i = 1; i <= n; i++) {
		dfs(i, 0);
		if (sum[i] & 1)
			continue;
		if (f[i] << 1 == sum[i])
			ans = min(ans, sum[i] / 2);
	}

	printf("%d\n", ans == 1e9 ? -1 : ans);
	return 0;
}
