#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <queue>
#define ll long long
#define mid ((l + r) >> 1)
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

int n, m, k, p;
int h[N + 1], a[N + 1];
ll per[N + 1];
priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > q;
ll ans;

inline bool check(ll val)
{
	while (!q.empty())
		q.pop();
	for (int i = 1; i <= n; i++) {
		per[i] = val;
		if (per[i] - 1ll * m * a[i] < 0)
			q.push(make_pair(per[i] / a[i], i));
	}
	int cnt = 0;

	while (!q.empty() && cnt <= k * m) {
		ll days = q.top().first;
		int id = q.top().second;
		pair<ll, int> s = q.top();
		q.pop();
		int day = cnt / k + 1;
		if (days < day)
			return false;
		per[id] += p;
		cnt++;
		if (per[id] - 1ll * m * a[id] < 0)
			q.push(make_pair(per[id] / a[id], id));
	}
	if (cnt > k * m)
		return false;
	for (int i = 1; i <= n; i++) {
		if (per[i] - 1ll * m * a[i] >= h[i])
			continue;
		ll w = h[i] - (per[i] - 1ll * m * a[i]), sum = w / p + (w % p != 0);
		cnt += sum;
		if (cnt > k * m)
			return false;
	}
	return true;
}
int main()
{
	n = read();
	m = read();
	k = read();
	p = read();
	for (int i = 1; i <= n; i++) {
		h[i] = read();
		a[i] = read();
	}

	ll l = 0, r = 6e12;

	while (l <= r) {
		if (check(mid)) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}

	printf("%lld\n", ans);
	return 0;
}
