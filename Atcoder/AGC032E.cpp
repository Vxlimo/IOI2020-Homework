#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
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

int n, m;
int a[N + 1];
int ans;

inline bool check(int val)
{
	val <<= 1;
	val = n - val;
	for (int i = val + 1, j = n; i < j; i++, j--)
		if (a[i] + a[j] < m)
			return false;
	return true;
}
int main()
{
	n = read() << 1;
	m = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();

	sort(a + 1, a + n + 1);
	int l = 0, r = (n >> 1) + 1;

	while (l + 1 < r) {
		int mid = (l + r) >> 1;
		if (check(mid))
			l = mid;
		else
			r = mid;
	}
	l <<= 1;
	l = n - l;

	for (int i = 1, j = l; i < j; i++, j--)
		ans = max(ans, a[i] + a[j]);
	for (int i = l + 1, j = n; i < j; i++, j--)
		ans = max(ans, (a[i] + a[j]) % m);
	printf("%d\n", ans);
	return 0;
}
