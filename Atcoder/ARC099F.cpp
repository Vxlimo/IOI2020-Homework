#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <map>
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
const int mod1 = 1e9 + 7;
const int mod2 = 1e9 + 9;
const int N = 5e5;

int n;
int f1[N + 1], f2[N + 1];
int fac1[N + 1], fac2[N + 1];
int pos[N + 1];
string opt;
ll ans;
map<pair<int, int>, int> mp;

inline void init()
{
	fac1[0] = fac2[0] = 1;
	for (int i = 1; i <= N; i++) {
		fac1[i] = 1ll * fac1[i - 1] * N % mod1;
		fac2[i] = 1ll * fac2[i - 1] * N % mod2;
	}
	return;
}
inline int pow(int x, int y, int mod)
{
	int ans = 1;

	while (y) {
		if (y & 1)
			ans = 1ll * ans * x % mod;
		x = 1ll * x * x % mod;
		y >>= 1;
	}
	return ans;
}
int main()
{
	init();
	n = read();
	cin >> opt;

	for (int i = 1; i <= n; i++) {
		if (opt[i - 1] == '+') {
			pos[i] = pos[i - 1];
			f1[i] = (1ll * f1[i - 1] + fac1[pos[i] + (N >> 1)]) % mod1;
			f2[i] = (1ll * f2[i - 1] + fac2[pos[i] + (N >> 1)]) % mod2;
		}
		if (opt[i - 1] == '-') {
			pos[i] = pos[i - 1];
			f1[i] = (1ll * f1[i - 1] - fac1[pos[i] + (N >> 1)] + mod1) % mod1;
			f2[i] = (1ll * f2[i - 1] - fac2[pos[i] + (N >> 1)] + mod2) % mod2;
		}
		if (opt[i - 1] == '<') {
			pos[i] = pos[i - 1] - 1;
			f1[i] = f1[i - 1];
			f2[i] = f2[i - 1];
		}
		if (opt[i - 1] == '>') {
			pos[i] = pos[i - 1] + 1;
			f1[i] = f1[i - 1];
			f2[i] = f2[i - 1];
		}
	}

	for (int i = n; i >= 1; i--) {
		mp[make_pair(f1[i], f2[i])]++;
		int w1, w2;
		if (pos[i - 1] < 0) {
			w1 = pow(pow(N, -pos[i - 1], mod1), mod1 - 2, mod1);
			w2 = pow(pow(N, -pos[i - 1], mod2), mod2 - 2, mod2);
		} else {
			w1 = pow(N, pos[i - 1], mod1);
			w2 = pow(N, pos[i - 1], mod2);
		}
		pair<int, int> sum = make_pair((1ll * f1[n] * w1 % mod1 + 1ll * f1[i - 1]) % mod1, (1ll * f2[n] * w2 % mod2 + 1ll * f2[i - 1]) % mod2);
		ans += mp[sum];
	}
	printf("%lld\n", ans);
	return 0;
}
