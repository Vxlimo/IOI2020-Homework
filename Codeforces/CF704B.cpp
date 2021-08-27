#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#define ll long long
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

int n, s, e;
int x[N + 1], a[N + 1], b[N + 1], c[N + 1], d[N + 1];
ll f[N + 1], g[N + 1];

inline void dp()
{
	for (int i = 1; i <= n; i++)
		g[i] = 1e18;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= n; j++)
			f[j] = 1e18;
		int p = i > s, q = i > e;
		if (i == s) {
			for (int j = q; j < i; j++) {
				if (g[j] == 1e18)
					continue;
				if (j)
					f[j] = min(f[j], g[j] + c[i]);
				f[j + 1] = min(f[j + 1], g[j] + d[i]);
			}
			memcpy(g, f, sizeof(ll) * (N + 1));
			continue;
		}
		if (i == e) {
			for (int j = p; j < i; j++) {
				if (g[j] == 1e18)
					continue;
				if (j)
					f[j] = min(f[j], g[j] + a[i]);
				f[j + 1] = min(f[j + 1], g[j] + b[i]);
			}
			memcpy(g, f, sizeof(ll) * (N + 1));
			continue;
		}
		for (int j = p + q; j < i; j++) {
			if (g[j] == 1e18)
				continue;
			int in = j - p, out = j - q;
			if (out > 0)
				f[j] = min(f[j], g[j] + a[i] + d[i]);
			if (j >= 2)
				f[j - 1] = min(f[j - 1], g[j] + a[i] + c[i]);
			if (in > 0)
				f[j] = min(f[j], g[j] + b[i] + c[i]);
			f[j + 1] = min(f[j + 1], g[j] + b[i] + d[i]);
		}
		memcpy(g, f, sizeof(ll) * (N + 1));
	}
	return;
}
int main()
{
	n = read();
	s = read();
	e = read();
	for (int i = 1; i <= n; i++)
		x[i] = read();
	for (int i = 1; i <= n; i++)
		a[i] = read() + x[i];
	for (int i = 1; i <= n; i++)
		b[i] = read() - x[i];
	for (int i = 1; i <= n; i++)
		c[i] = read() + x[i];
	for (int i = 1; i <= n; i++)
		d[i] = read() - x[i];

	dp();

	printf("%lld\n", f[1]);
	return 0;
}
