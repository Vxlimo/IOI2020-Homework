#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <set>
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
const int N = 2e5;

int n;
int fa[N + 1], f[N + 1];
struct Node {
	int	num, val0, val1;
	ll	val;
	inline bool operator <(Node a) const
	{
		if (1ll * val0 * a.val1 == 1ll * val1 * a.val0)
			return num < a.num;
		return 1ll * val0 * a.val1 > 1ll * val1 * a.val0;
	}
} node[N + 1];
set<Node> s;

inline int getfa(int x)
{
	if (f[x] == x)
		return x;
	f[x] = getfa(f[x]);
	return f[x];
}
inline void solve()
{
	for (int i = 1; i <= n; i++)
		f[i] = i;
	while (!s.empty()) {
		Node now = *s.begin();
		if (now.num == 1) {
			s.erase(now);
			continue;
		}
		Node faa = node[getfa(fa[now.num])];
		s.erase(now);
		s.erase(faa);
		f[now.num] = faa.num;
		faa.val += now.val;
		faa.val += 1ll * now.val0 * faa.val1;
		faa.val0 += now.val0;
		faa.val1 += now.val1;
		node[now.num] = now;
		node[faa.num] = faa;
		s.insert(faa);
	}
	return;
}
int main()
{
	n = read();
	for (int i = 2; i <= n; i++)
		fa[i] = read();
	for (int i = 1; i <= n; i++) {
		node[i].num = i;
		node[i].val = 0;
		int x = read();
		if (x) {
			node[i].val0 = 0;
			node[i].val1 = 1;
		} else {
			node[i].val0 = 1;
			node[i].val1 = 0;
		}
		s.insert(node[i]);
	}

	solve();

	printf("%lld\n", node[1].val);
	return 0;
}
