#include <iostream>
#include <cstdlib>
#include <cstdio>
#define ll long long
using namespace std;
inline ll read()
{
	ll f = 1, x = 0;
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

int tt;
int n;
ll l[5], r[5], L[5], R[5];
struct Node {
	ll x, y, z;
} ans;

inline void make()
{
	ans = { L[2], L[3], L[4] };
	if (ans.x + ans.y + ans.z < L[1]) {
		if (L[1] - ans.x - ans.y - ans.z <= R[4] - L[4]) {
			ans.z += min(L[1] - ans.x - ans.y - ans.z, R[4] - L[4]);
			return;
		}
		ans.z = R[4];
		if (L[1] - ans.x - ans.y - ans.z <= R[3] - L[3]) {
			ans.y += min(L[1] - ans.x - ans.y - ans.z, R[3] - L[3]);
			return;
		}
		ans.y = R[3];
		ans.x += min(L[1] - ans.x - ans.y - ans.z, R[2] - L[2]);
	}
	return;
}
inline bool check(ll d)
{
	bool flag = true;

	for (int i = 1; i <= 4; i++) {
		l[i] -= d;
		r[i] += d;
		if (l[i] > r[i])
			flag = false;
	}
	if (!flag) {
		for (int i = 1; i <= 4; i++) {
			l[i] += d;
			r[i] -= d;
		}
		return false;
	}
	for (int i = 0; i < 2; i++) {
		flag = true;
		for (int j = 1; j <= 4; j++) {
			L[j] = l[j];
			R[j] = r[j];
			if ((L[j] & 1) != i)
				L[j]++;
			if ((R[j] & 1) != i)
				R[j]--;
			if (L[j] > R[j]) {
				flag = false;
				break;
			}
		}
		if (L[2] + L[3] + L[4] > R[1] || R[2] + R[3] + R[4] < L[1])
			flag = false;
		if (!flag)
			continue;
		make();
		break;
	}
	for (int i = 1; i <= 4; i++) {
		l[i] += d;
		r[i] -= d;
	}
	return flag;
}
int main()
{
	tt = read();

	while (tt--) {
		for (int i = 1; i <= 4; i++) {
			l[i] = -3e18;
			r[i] = 3e18;
		}
		n = read();
		for (int i = 1; i <= n; i++) {
			ll x = read(), y = read(), z = read();
			l[1] = max(l[1], x + y + z);
			r[1] = min(r[1], x + y + z);
			l[2] = max(l[2], -x + y + z);
			r[2] = min(r[2], -x + y + z);
			l[3] = max(l[3], x - y + z);
			r[3] = min(r[3], x - y + z);
			l[4] = max(l[4], x + y - z);
			r[4] = min(r[4], x + y - z);
		}
		ll l = 0, r = 3e18;
		while (l <= r) {
			ll mid = (l + r) >> 1;
			if (check(mid))
				r = mid - 1;
			else
				l = mid + 1;
		}
		printf("%lld %lld %lld\n", (ans.y + ans.z) / 2, (ans.x + ans.z) / 2, (ans.x + ans.y) / 2);
	}

	return 0;
}
