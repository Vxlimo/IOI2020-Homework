#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
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
const int N = 100;
const int mod = 1e9 + 7;

int n;
int hight[N + 1];

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
inline pair<int, int> solve(int l, int r, int la)
{
	if (r < l)
		return make_pair(1, 0);
	vector<int> pos;
	int h = 1e9, mul1 = 1, mul2 = 1;

	for (int i = l; i <= r; i++)
		h = min(h, hight[i]);
	pos.push_back(l - 1);
	for (int i = l; i <= r; i++)
		if (hight[i] == h)
			pos.push_back(i);
	pos.push_back(r + 1);
	for (int i = 1; i < pos.size(); i++) {
		pair<int, int> nxt = solve(pos[i - 1] + 1, pos[i] - 1, h);
		mul1 = 1ll * mul1 * nxt.first % mod;
		mul2 = 1ll * mul2 * (nxt.first + nxt.second) % mod;
	}
	return make_pair(1ll * pow(2, h - la) * mul1 % mod, (1ll * pow(2, pos.size() - 2) * mul2 % mod + 1ll * (pow(2, h - la) - 2) * mul1 % mod) % mod);
}
int main()
{
	n = read();
	for (int i = 1; i <= n; i++)
		hight[i] = read();

	printf("%d\n", solve(1, n, 0).second);

	return 0;
}
