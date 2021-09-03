#include <iostream>
#include <cstdlib>
#include <cstdio>
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
const int M = 1e5;
const int mod = 1e9 + 7;

int n, m;
struct Edge {
	int to, next;
} edge[M * 2 + 1];
int start[N + 1], tot, d[N + 1], vis[N + 1], type[N + 1], tag[N + 1];
int f[2][2][2], g[2][2][2];
int w[2][N + 1], cnt;
int ans = 1;

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
inline void dp1(int u)
{
	memset(g, 0, sizeof(int) * 8);
	if (tag[u])
		g[0][0 ^ type[u]][0] = g[1][1 ^ type[u]][0] = 1;
	else
		g[0][0][0] = g[0][1][0] = 1;
	vis[u] = 1;
	for (int i = start[u]; i; i = edge[i].to) {
		int v = edge[i].to;
		if (!vis[v]) {
			u = v;
			break;
		}
	}
	while (!vis[u]) {
		vis[u] = 1;
		memset(f, 0, sizeof(int) * 8);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++)
				for (int k = 0; k < 2; k++)
					f[i ^ (j | k)][k ^ type[u]][0] = (f[i ^ (j | k)][k ^ type[u]][0] + g[i][j][0]) % mod;
		}
		memcpy(g, f, sizeof(int) * 8);
		for (int i = start[u]; i; i = edge[i].next) {
			int v = edge[i].to;
			if (!vis[v]) {
				u = v;
				break;
			}
		}
	}
	if (tag[u]) {
		w[0][++cnt] = (f[0][0][0] + f[1][1][0]) % mod;
		w[1][cnt] = (f[1][0][0] + f[0][1][0]) % mod;
	} else {
		w[0][++cnt] = (f[0][0][0] + f[0][1][0]) % mod;
		w[1][cnt] = (f[1][0][0] + f[1][1][0]) % mod;
	}
	return;
}
inline void dp2(int u)
{
	memset(g, 0, sizeof(int) * 8);
	g[0][0 ^ type[u]][0] = g[0][1 ^ type[u]][1] = 1;
	vis[u] = 1;
	for (int i = start[u]; i; i = edge[i].next) {
		int v = edge[i].to;
		if (!vis[v]) {
			u = v;
			break;
		}
	}
	while (!vis[u]) {
		vis[u] = 1;
		memset(f, 0, sizeof(int) * 8);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++)
					for (int fi = 0; fi < 2; fi++)
						f[i ^ (j | k)][k ^ type[u]][fi] = (f[i ^ (j | k)][k ^ type[u]][fi] + g[i][j][fi]) % mod;
			}
		}
		memcpy(g, f, sizeof(int) * 8);
		for (int i = start[u]; i; i = edge[i].next) {
			int v = edge[i].to;
			if (!vis[v]) {
				u = v;
				break;
			}
		}
	}
	w[0][++cnt] = (1ll * f[0][0][0] + f[1][0][1] + f[1][1][0] + f[1][1][1]) % mod;
	w[1][cnt] = (1ll * f[1][0][0] + f[0][0][1] + f[0][1][0] + f[0][1][1]) % mod;
	return;
}
inline void dp()
{
	memset(g, 0, sizeof(int) * 8);
	g[0][0][0] = 1;
	for (int i = 1; i <= cnt; i++) {
		memset(f, 0, sizeof(int) * 8);
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
				f[j ^ k][0][0] = (f[j ^ k][0][0] + 1ll * g[j][0][0] * w[k][i] % mod) % mod;
		memcpy(g, f, sizeof(int) * 8);
	}
	return;
}
int main()
{
	m = read();
	n = read();
	for (int i = 1; i <= m; i++) {
		int k = read();
		if (k == 1) {
			int x = read();
			if (tag[abs(x)]) {
				if (tag[abs(x)] * x < 0)
					tag[abs(x)] = 2;
				else
					tag[abs(x)] = 3;
				continue;
			}
			if (x > 0) {
				tag[x] = 1;
				type[x] ^= 1;
			} else {
				tag[-x] = -1;
			}
		} else {
			int x = read(), y = read();
			if (x + y == 0) {
				w[0][++cnt] = 0;
				w[1][cnt] = 2;
				vis[abs(x)] = 1;
				continue;
			}
			if (x == y) {
				w[0][++cnt] = 1;
				w[1][cnt] = 1;
				vis[abs(x)] = 1;
				continue;
			}
			addedge(abs(x), abs(y));
			if (x > 0)
				type[x] ^= 1;
			if (y > 0)
				type[y] ^= 1;
		}
	}

	for (int i = 1; i <= n; i++)
		if (!vis[i] && d[i] == 1)
			dp1(i);
	for (int i = 1; i <= n; i++)
		if (!vis[i] && d[i] == 2)
			dp2(i);
	for (int i = 1; i <= n; i++) {
		if (vis[i])
			continue;
		if (tag[i] == 2) {
			w[0][++cnt] = 0;
			w[1][cnt] = 2;
			continue;
		}
		if (tag[i] == 3) {
			w[0][++cnt] = 2;
			w[1][cnt] = 0;
			continue;
		}
		if (tag[i]) {
			w[0][++cnt] = 1;
			w[1][cnt] = 1;
		} else {
			ans = 2ll * ans % mod;
		}
	}
	dp();

	printf("%d\n", 1ll * ans * f[1][0][0] % mod);
	return 0;
}
