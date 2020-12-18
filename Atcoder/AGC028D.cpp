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
const int N = 600;
const int mod = 1e9 + 7;

int n, k;
int to[N + 1];
int f[N + 1][N + 1], g[N + 1];
int ans;

inline void dp()
{
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j += 2) {
			int sum1 = j - i + 1, sum2;
			bool flag = true;
			for (int k = i; k <= j; k++) {
				if (to[k]) {
					sum1--;
					if (to[k] < i || to[k] > j) {
						flag = false;
						break;
					}
				}
			}
			if (flag) {
				f[i][j] = g[sum1];
				sum2 = !to[j];
				for (int k = j - 1; k >= i; k--) {
					f[i][j] = (f[i][j] - 1ll * f[i][k] * g[sum2] + 1ll * mod) % mod;
					sum2 += !to[k];
				}
				ans = (ans + 1ll * f[i][j] * g[n - (k << 1) - sum1]) % mod;
			}
		}
	}
	return;
}
int main()
{
	n = read() << 1;
	k = read();
	for (int i = 1; i <= k; i++) {
		int x = read(), y = read();
		to[x] = y;
		to[y] = x;
	}
	g[0] = 1;
	for (int i = 2; i <= n; i += 2)
		g[i] = 1ll * g[i - 2] * (i - 1) % mod;

	dp();

	printf("%d\n", ans);
	return 0;
}
