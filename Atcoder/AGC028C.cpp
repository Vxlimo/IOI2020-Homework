#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
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

int n;
int t[(N << 1) + 1];
struct Node {
	int x, num;
} node[(N << 1) + 1];
ll ans;

inline bool compare(Node a, Node b)
{
	return a.x < b.x;
}
int main()
{
	n = read();
	for (int i = 1; i <= n; i++) {
		int x = read();
		node[((i - 1) << 1) + 1] = Node{ x, ((i - 1) << 1) + 1 };
		x = read();
		node[i << 1] = Node{ x, i << 1 };
	}

	sort(node + 1, node + (n << 1) + 1, compare);
	for (int i = 1; i <= n; i++) {
		ans += (ll)node[i].x;
		t[node[i].num]++;
	}
	bool flag = true, flag2 = true, flag3 = true;
	for (int i = 1; i <= n; i++) {
		if (t[((i - 1) << 1) + 1])
			flag2 = false;
		if (t[i << 1])
			flag3 = false;
		if (t[((i - 1) << 1) + 1] && t[i << 1])
			flag = false;
	}
	if (flag && !flag2 && !flag3) {
		if ((node[n].num + 1) >> 1 != (node[n + 1].num + 1) >> 1)
			ans += (ll)node[n + 1].x - (ll)node[n].x;
		else
			ans += (ll)min(node[n + 2].x - node[n].x, node[n + 1].x - node[n - 1].x);
	}

	printf("%lld\n", ans);
	return 0;
}
