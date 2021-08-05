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
const int N = 1e5;

int n, s, lx, rx;
ll ans, lp, rp;
int x[N + 1], p[N + 1];

inline void solve()
{
	lx = 1;
	rx = n;
	lp = p[lx];
	rp = p[rx];
	int la = 0;
	while (s < x[rx] && s > x[lx]) {
		if (lp < rp) {
			if (la > lx || !la)
				ans += 1ll * (x[rx] - x[lx]);
			rp += lp;
			lx++;
			lp = p[lx];
			la = lx - 1;
		} else {
			if (la < rx || !la)
				ans += 1ll * (x[rx] - x[lx]);
			lp += rp;
			rx--;
			rp = p[rx];
			la = rx + 1;
		}
	}
	if (s > x[rx])
		ans += 1ll * (s - x[lx]);
	else
		ans += 1ll * (x[rx] - s);
	return;
}
int main()
{
	n = read();
	s = read();
	for (int i = 1; i <= n; i++) {
		x[i] = read();
		p[i] = read();
	}

	solve();

	printf("%lld\n", ans);
	return 0;
}
