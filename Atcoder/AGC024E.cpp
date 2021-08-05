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
const int N = 300;

int n, m, mod;
int f[N + 2][N + 1];
int C[N + 1][N + 1];

inline int pow(int x, int y)
{
	int num = 1;

	while (y) {
		if (y & 1)
			num = 1ll * num * x % mod;
		x = 1ll * x * x % mod;
		y >>= 1;
	}
	return num;
}
inline void init()
{
	for (int i = 0; i <= N; i++)
		C[i][0] = 1;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= i; j++)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
	return;
}
inline void dp()
{
	for (int i = 0; i <= m; i++)
		f[1][i] = 1;
	for (int i = 2; i <= n + 1; i++) {
		for (int k = 1; k < i; k++) {
			int sum = 0;
			for (int j = m; j >= 0; j--) {
				f[i][j] = (f[i][j] + 1ll * C[i - 2][k - 1] * f[i - k][j] % mod * sum % mod) % mod;
				sum = (sum + f[k][j]) % mod;
			}
		}
	}
	return;
}
int main()
{
	n = read();
	m = read();
	mod = read();
	init();

	dp();

	printf("%d\n", f[n + 1][0]);
	return 0;
}
