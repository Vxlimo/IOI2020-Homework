#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <map>
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
const int mod = 1e9 + 7;

int n, m;
int a[N + 1], b[N + 1];
struct Node {
	int x, y;
	inline bool operator <(Node a) const
	{
		return x == a.x?y < a.y:x < a.x;
	}
} node[N + 1];
int pos[(N << 1) + 1], tot, cnt;
int f[N + 1];
map<int, int> to;
map<Node, int > appear;
int ans = 1;
namespace bit
{
int tr[(N << 1) + 1];
inline int lowbit(int x)
{
	return x & (-x);
}
inline void update(int pos, int val)
{
	while (pos <= (N << 1)) {
		tr[pos] = (tr[pos] + val) % mod;
		pos += lowbit(pos);
	}
	return;
}
inline int query(int pos)
{
	int sum = 0;

	while (pos) {
		sum = (sum + tr[pos]) % mod;
		pos -= lowbit(pos);
	}
	return sum;
}
}

inline void dp()
{
	for (int i = 1; i <= tot; i++)
		node[i] = { to[node[i].x], to[node[i].y] };
	sort(node + 1, node + tot + 1);
	int la = 0;

	node[0] = { 0, 0 };
	for (int i = 1; i <= tot; i++) {
		if (appear.count(node[i]))
			continue;
		if (node[i].x != node[la].x) {
			for (int j = max(1, la); j < i; j++)
				bit::update(node[j].y, f[j]);
			la = i;
		}
		f[i] = (bit::query(node[i].y - 1) + 1) % mod;
		appear[node[i]] = 1;
	}
	return;
}
int main()
{
	n = read();
	m = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	for (int i = 1; i <= m; i++)
		b[i] = read();
	for (int i = 1; i <= n; i++) {
		int l = upper_bound(b + 1, b + m + 1, a[i]) - b - 1, r = lower_bound(b + 1, b + m + 1, a[i]) - b;
		if (l < 1 || r > m)
			continue;
		if (a[i] == b[l] || b[r] == a[i])
			continue;
		node[++tot] = { a[i] - b[l], b[r] - a[i] };
		pos[(tot << 1) - 1] = node[tot].x;
		pos[tot << 1] = node[tot].y;
	}
	sort(pos + 1, pos + (tot << 1) + 1);
	for (int i = 1; i <= tot << 1; i++)
		if (!to.count(pos[i]))
			to[pos[i]] = ++cnt;

	dp();

	for (int i = 1; i <= tot; i++)
		ans = (ans + f[i]) % mod;
	printf("%d\n", ans);
	return 0;
}
