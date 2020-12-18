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
const int N = 5e3;
const int mod = 1e9 + 7;

int n;
struct Edge {
	int to, next;
} edge[(N << 1) + 1];
int start[N + 1], tot;
int f[N + 1][N + 1], g[N + 1], h[N + 1], sz[N + 1];

inline void addedge(int u, int v)
{
	edge[++tot] = Edge{ v, start[u] };
	start[u] = tot;
	edge[++tot] = Edge{ u, start[v] };
	start[v] = tot;
	return;
}
inline void dp(int u, int fa)
{
	f[u][1] = sz[u] = 1;
	for (int i = start[u]; i; i = edge[i].next) {
		int v = edge[i].to;
		if (v != fa) {
			dp(v, u);
			for (int j = 1; j <= sz[u] + sz[v]; j++)
				h[j] = 0;
			for (int j = 1; j <= sz[u]; j++)
				for (int k = 0; k <= sz[v]; k++)
					h[j + k] = (h[j + k] + 1ll * f[u][j] * f[v][k] % mod) % mod;
			sz[u] += sz[v];
			for (int j = 1; j <= sz[u]; j++)
				f[u][j] = h[j];
		}
	}
	for (int i = 2; i <= sz[u]; i += 2)
		f[u][0] = (f[u][0] - 1ll * f[u][i] * g[i] % mod + mod) % mod;
	return;
}
int main()
{
	n = read();
	for (int i = 1; i < n; i++)
		addedge(read(), read());
	g[0] = 1;
	for (int i = 2; i <= n; i += 2)
		g[i] = 1ll * g[i - 2] * (i - 1) % mod;

	dp(1, 0);

	printf("%d\n", (-f[1][0] + mod) % mod);
	return 0;
}
