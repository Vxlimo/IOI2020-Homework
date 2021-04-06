#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
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
const int N = 2e5;

int n, q;
struct Seg {
	int root[N * 2 + 1], tr[N * 75 + 1], lson[N * 75 + 1], rson[N * 75 + 1], tot;
	inline int update(int now, int l, int r, int pos)
	{
		if (!now)
			now = ++tot;
		if (l == r) {
			tr[now]++;
			return now;
		}
		if (pos <= mid)
			lson[now] = update(lson[now], l, mid, pos);
		else
			rson[now] = update(rson[now], mid + 1, r, pos);
		tr[now] = tr[lson[now]] + tr[rson[now]];
		return now;
	}
	inline int query(int now, int l, int r, int L, int R)
	{
		if (!now)
			return 0;
		if (l >= L && r <= R)
			return tr[now];
		int sum = 0;

		if (mid >= L)
			sum += query(lson[now], l, mid, L, R);
		if (mid < R)
			sum += query(rson[now], mid + 1, r, L, R);
		return sum;
	}
	inline int merge(int x, int y)
	{
		if (!y)
			return x + y;
		int z = ++tot;

		if (!x) {
			tr[z] = tr[y];
			lson[z] = lson[y];
			rson[z] = rson[y];
			return z;
		}
		tr[z] = tr[x] + tr[y];
		lson[z] = merge(lson[x], lson[y]);
		rson[z] = merge(rson[x], rson[y]);
		return z;
	}
} seg;
struct SAM {
	int		tr[N * 2 + 1][26], len[N * 2 + 1], link[N * 2 + 1], sz = 1, last;
	vector<int>	to[N * 2 + 1];
	int		at[N + 1], up[N * 2 + 1];
	inline void extend(int x)
	{
		if (tr[last][x]) {
			int p = last, q = tr[p][x];
			if (len[p] + 1 == len[q]) {
				last = q;
			} else {
				int w = ++sz;
				memcpy(tr[w], tr[q], sizeof(int) * 26);
				len[w] = len[p] + 1;
				link[w] = link[q];
				link[q] = w;
				while (p && tr[p][x] == q) {
					tr[p][x] = w;
					p = link[p];
				}
				last = w;
			}
		} else {
			int p = last, cur = ++sz;
			len[cur] = len[last] + 1;
			while (p && !tr[p][x]) {
				tr[p][x] = cur;
				p = link[p];
			}
			if (!p) {
				link[cur] = 1;
			} else {
				int q = tr[p][x];
				if (len[p] + 1 == len[q]) {
					link[cur] = q;
				} else {
					int w = ++sz;
					memcpy(tr[w], tr[q], sizeof(int) * 26);
					len[w] = len[p] + 1;
					link[w] = link[q];
					link[q] = link[cur] = w;
					while (p && tr[p][x] == q) {
						tr[p][x] = w;
						p = link[p];
					}
				}
			}
			last = cur;
		}
		return;
	}
	inline void merge(int u)
	{
		for (vector<int>::iterator it = to[u].begin(); it != to[u].end(); it++) {
			int v = *it;
			if (len[u] == len[v])
				up[v] = up[u];
			else
				up[v] = v;
			merge(v);
			seg.root[u] = seg.merge(seg.root[u], seg.root[v]);
		}
		return;
	}
} sam;

int main()
{
	n = read();
	q = read();

	for (int i = 1; i <= n; i++) {
		string s;
		cin >> s;
		sam.last = 1;
		for (int j = 0; j < s.size(); j++) {
			sam.extend(s[j] - 'a');
			seg.root[sam.last] = seg.update(seg.root[sam.last], 1, n, i);
		}
		sam.at[i] = sam.last;
	}
	for (int i = 2; i <= sam.sz; i++)
		sam.to[sam.link[i]].push_back(i);
	sam.up[1] = 1;
	sam.merge(1);

	for (int i = 1; i <= q; i++) {
		int l = read(), r = read(), x = read();
		printf("%d\n", seg.query(seg.root[sam.up[sam.at[x]]], 1, n, l, r));
	}
	return 0;
}
