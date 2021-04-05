#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#define ll long long
#define lson (now << 1)
#define rson ((now << 1) + 1)
#define mid ((l + r) >> 1)
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
const int N = 5e4;

int n, m, mod;
ll k;
int x[N + 1];
struct Change {
	ll pos, newx;
	inline bool operator <(Change a) const
	{
		return pos < a.pos;
	}
} cge[N + 1];
struct Mat {
	int mat[3][3];
	inline void init()
	{
		mat[1][1] = mat[2][2] = 1;
		mat[1][2] = mat[2][1] = 0;
		return;
	}
	inline friend Mat operator *(Mat a, Mat b)
	{
		Mat c;

		for (int i = 1; i <= 2; i++) {
			for (int j = 1; j <= 2; j++) {
				c.mat[i][j] = 0;
				for (int k = 1; k <= 2; k++)
					c.mat[i][j] = (c.mat[i][j] + 1ll * a.mat[i][k] * b.mat[k][j] % mod) % mod;
			}
		}
		return c;
	}
} s[N + 1], ans;
struct Seg {
	Mat tr[N * 4 + 1];
	inline void pushup(int now)
	{
		tr[now] = tr[rson] * tr[lson];
		return;
	}
	inline void build(int now, int l, int r)
	{
		if (l == r) {
			tr[now] = s[l];
			return;
		}
		build(lson, l, mid);
		build(rson, mid + 1, r);
		pushup(now);
		return;
	}
	inline void update(int now, int l, int r, int pos)
	{
		if (l == r) {
			tr[now] = s[pos];
			return;
		}
		if (pos <= mid)
			update(lson, l, mid, pos);
		else
			update(rson, mid + 1, r, pos);
		pushup(now);
		return;
	}
} seg;

inline Mat pow(Mat x, ll y)
{
	Mat sum;

	sum.init();
	while (y) {
		if (y & 1)
			sum = sum * x;
		x = x * x;
		y >>= 1;
	}
	return sum;
}
int main()
{
	k = read() - 1;
	if (k == -1) {
		printf("0\n");
		return 0;
	}
	mod = read();
	n = read();
	for (int i = 0; i < n; i++)
		x[i] = read() % mod;
	m = read();
	int w = 1;

	for (int i = 1; i <= m; i++) {
		cge[w] = { read(), read() % mod };
		if (cge[w].pos < n)
			x[cge[w].pos] = cge[w].newx;
		else
			w++;
	}
	m = w - 1;
	for (int i = 1; i <= n; i++) {
		s[i].mat[1][1] = x[i % n];
		s[i].mat[1][2] = x[i - 1];
		s[i].mat[2][1] = 1;
		s[i].mat[2][2] = 0;
	}

	ans.init();
	seg.build(1, 1, n);
	sort(cge + 1, cge + m + 1);
	ll j = 0;
	bool flag = false;

	for (int i = 1; i <= m && cge[i].pos <= k;) {
		if (flag && (cge[i].pos - j - 1) / n > 0) {
			ans = seg.tr[1] * ans;
			j += n;
			flag = false;
			s[1].mat[1][2] = x[0];
			seg.update(1, 1, n, 1);
		}
		ans = pow(seg.tr[1], (cge[i].pos - j - 1) / n) * ans;
		j += 1ll * (cge[i].pos - j - 1) / n * n;
		int w = i;
		while (i <= m && cge[i].pos <= j + n && cge[i].pos <= k) {
			s[cge[i].pos - j].mat[1][1] = cge[i].newx;
			seg.update(1, 1, n, cge[i].pos - j);
			if (cge[i].pos - j != n) {
				s[cge[i].pos - j + 1].mat[1][2] = cge[i].newx;
				seg.update(1, 1, n, cge[i].pos - j + 1);
			}
			i++;
		}
		if (k - j < n)
			for (int l = 1; l <= k - j; l++)
				ans = s[l] * ans;
		else
			ans = seg.tr[1] * ans;
		if (flag) {
			flag = false;
			s[1].mat[1][2] = x[0];
			seg.update(1, 1, n, 1);
		}
		for (int l = w; l < i; l++) {
			s[cge[l].pos - j].mat[1][1] = x[(cge[l].pos - j) % n];
			seg.update(1, 1, n, cge[l].pos - j);
			if (cge[l].pos - j != n) {
				s[cge[l].pos - j + 1].mat[1][2] = x[cge[l].pos - j];
				seg.update(1, 1, n, cge[l].pos - j + 1);
			}
		}
		if (cge[i - 1].pos - j == n) {
			flag = true;
			s[1].mat[1][2] = cge[i - 1].newx;
			seg.update(1, 1, n, 1);
		}
		j = min(k, j + n);
	}
	if (flag) {
		if (k - j < n)
			for (int i = 1; i <= k - j; i++)
				ans = s[i] * ans;
		else
			ans = seg.tr[1] * ans;
		j = min(k, j + n);
		flag = false;
		s[1].mat[1][2] = x[0];
		seg.update(1, 1, n, 1);
	}
	ans = pow(seg.tr[1], (k - j) / n) * ans;
	j += (k - j) / n * n;
	for (int i = 1; i <= k - j; i++)
		ans = s[i] * ans;

	printf("%d\n", ans.mat[1][1]);
	return 0;
}
