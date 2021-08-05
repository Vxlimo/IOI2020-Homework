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
const int N = 2e5;

int n;
int a[N + 1];
struct Node {
	int len, val;
} st[N + 1];
int top;
int ans;

inline void ins(int len, int k)
{
	while (st[top].len > len)
		top--;
	if (st[top].len == len) {
		st[top].val++;
		if (top > 1 && st[top].val == k) {
			top--;
			ins(len - 1, k);
		}
	} else {
		st[++top] = Node{ len, 1 };
	}
	return;
}
inline bool check(int k)
{
	top = 1;
	st[top] = Node{ 0, 0 };
	for (int i = 2; i <= n; i++)
		if (a[i] <= a[i - 1])
			ins(a[i], k);
	return !st[1].val;
}
int main()
{
	n = read();
	bool flag = true;

	for (int i = 1; i <= n; i++) {
		a[i] = read();
		if (a[i] <= a[i - 1])
			flag = false;
	}
	if (flag) {
		printf("1\n");
		return 0;
	}

	int l = 2, r = n;

	while (l <= r) {
		int mid = (l + r) >> 1;
		if (check(mid)) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	printf("%d\n", ans);
	return 0;
}
