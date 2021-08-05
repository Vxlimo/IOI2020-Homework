#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <algorithm>
#include <queue>
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
const int N = 150;

int n, m;
struct Flt {
	int u, v, d;
	inline bool operator <(Flt x) const
	{
		return d < x.d;
	}
} flt[N + 1];
struct Mat {
	bitset<N> mat[N];
	inline void init()
	{
		for (int i = 0; i < n; i++)
			mat[i][i] = 1;
		return;
	}
	inline Mat operator *(Mat x) const
	{
		Mat y;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				if (mat[i][j])
					y.mat[i] |= x.mat[j];
		}
		return y;
	}
};
queue<int> q;
int dis[N], ans = 2e9;

inline Mat pow(Mat x, int y)
{
	Mat ans;

	ans.init();
	while (y) {
		if (y & 1)
			ans = ans * x;
		x = x * x;
		y >>= 1;
	}
	return ans;
}
int main()
{
	n = read();
	m = read();
	for (int i = 1; i <= m; i++)
		flt[i] = { read() - 1, read() - 1, read() };
	sort(flt + 1, flt + m + 1);

	Mat to, reach;

	reach.mat[0][0] = 1;
	int la = 0;

	for (int i = 1; i <= m; i++) {
		if (flt[i].d >= ans)
			break;
		reach = reach * pow(to, flt[i].d - la);
		to.mat[flt[i].u][flt[i].v] = 1;
		la = flt[i].d;
		for (int j = 0; j < n; j++) {
			if (reach.mat[0][j]) {
				dis[j] = 0;
				q.push(j);
			} else {
				dis[j] = 2e9;
			}
		}
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for (int j = 0; j < n; j++) {
				if (to.mat[u][j] && dis[j] > dis[u] + 1) {
					dis[j] = dis[u] + 1;
					q.push(j);
				}
			}
		}
		if (dis[n - 1] != 2e9)
			ans = min(ans, dis[n - 1] + la);
	}

	if (ans == 2e9)
		printf("Impossible\n");
	else
		printf("%d\n", ans);
	return 0;
}
