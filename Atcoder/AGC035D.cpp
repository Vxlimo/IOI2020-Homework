#include <iostream>
#include <cstdlib>
#include <cstdio>
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
const int N = 18;

int n;
int a[N + 1];

inline ll dfs(int l, int r, int lx, int rx)
{
	if (r - l + 1 <= 2)
		return 0;
	ll ans = 1e18;

	for (int i = l + 1; i <= r - 1; i++)
		ans = min(ans, dfs(l, i, lx, lx + rx) + dfs(i, r, lx + rx, rx) + 1ll * (lx + rx) * a[i]);
	return ans;
}
int main()
{
	n = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();

	printf("%lld\n", a[1] + a[n] + dfs(1, n, 1, 1));

	return 0;
}
