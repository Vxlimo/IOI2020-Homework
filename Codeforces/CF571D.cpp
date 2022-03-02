#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
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
const int N = 5e5;

int n, m;
int fa1[N + 1], sz1[N + 1], time1[N + 1], fa2[N + 1], sz2[N + 1], time2[N + 1];
struct Opt {
	ll val, time;
	inline bool operator <(Opt x) const
	{
		return time < x.time;
	}
};
Opt change[N + 1];
vector<Opt> add[N + 1];

inline int gfa1(int x)
{
	if (fa1[x] != x)
		return gfa1(fa1[x]);
	return x;
}
inline int gfa2(int x)
{
	if (fa2[x] != x)
		return gfa2(fa2[x]);
	return x;
}
int main()
{
	n = read();
	m = read();
	for (int i = 1; i <= n; i++) {
		fa1[i] = fa2[i] = i;
		sz1[i] = sz2[i] = 1;
	}

	for (int i = 1; i <= m; i++) {
		char opt = getchar();
		int x = read(), y;
		if (opt == 'U') {
			y = read();
			x = gfa1(x);
			y = gfa1(y);
			if (sz1[x] < sz1[y])
				swap(x, y);
			fa1[y] = x;
			sz1[x] += sz1[y];
			time1[y] = i;
		}
		if (opt == 'M') {
			y = read();
			x = gfa2(x);
			y = gfa2(y);
			if (sz2[x] < sz2[y])
				swap(x, y);
			fa2[y] = x;
			sz2[x] += sz2[y];
			time2[y] = i;
		}
		if (opt == 'A') {
			x = gfa1(x);
			add[x].push_back(Opt{ 1ll * sz1[x] + (add[x].size() ? add[x][add[x].size() - 1].val : 0), i });
		}
		if (opt == 'Z')
			change[gfa2(x)] = Opt{ 0, i };
		if (opt == 'Q') {
			int timme = 0, time = 0, now = x;
			ll val = 0;
			while (true) {
				if (change[now].time > timme && change[now].time > time) {
					val = change[now].val;
					time = change[now].time;
				}
				if (now == fa2[now])
					break;
				timme = max(time2[now], timme);
				now = fa2[now];
			}
			now = x;
			while (true) {
				if (add[now].size()) {
					vector<Opt>::iterator it = upper_bound(add[now].begin(), add[now].end(), Opt{ 0, time });
					val += add[now][add[now].size() - 1].val;
					if (it != add[now].begin()) {
						it--;
						val -= (*it).val;
					}
				}
				if (now == fa1[now])
					break;
				time = max(time, time1[now]);
				now = fa1[now];
			}
			printf("%lld\n", val);
		}
	}

	return 0;
}
