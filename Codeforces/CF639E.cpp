#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
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
const int N = 1.5e5;
const double eps = 1e-8;

int n;
struct Node {
	int	p, t;
	ll	late, early;
	inline bool operator <(Node x) const
	{
		return p < x.p;
	}
} node[N + 1];
ll sumt;
set<double> s;
double score[N + 1];

inline bool compare(Node x, Node y)
{
	return 1.0 * x.t / x.p < 1.0 * y.t / y.p;
}
inline bool check(double val)
{
	s.clear();
	int last = 0;

	for (int i = 1; i <= n; i++) {
		if (node[i].p != node[i - 1].p) {
			for (int j = last + 1; j < i; j++)
				s.insert(score[j]);
			last = i - 1;
		}
		score[i] = 1.0 * node[i].p * (1.0 - val * node[i].late / sumt);
		if (s.upper_bound(score[i]) != s.end())
			return false;
		score[i] = 1.0 * node[i].p * (1.0 - val * (node[i].early + node[i].t) / sumt);
	}
	return true;
}
int main()
{
	n = read();
	for (int i = 1; i <= n; i++)
		node[i].p = read();
	for (int i = 1; i <= n; i++)
		node[i].t = read();
	sort(node + 1, node + n + 1, compare);
	ll j = 0;

	for (int i = 1; i <= n; i++) {
		if (i == 1 || 1.0 * node[i].t / node[i].p != 1.0 * node[i - 1].t / node[i - 1].p)
			j = sumt;
		node[i].early = j;
		sumt += node[i].t;
		node[i].late = sumt;
	}
	for (int i = n - 1; i >= 1; i--)
		if (1.0 * node[i].t / node[i].p == 1.0 * node[i + 1].t / node[i + 1].p)
			node[i].late = node[i + 1].late;
	sort(node + 1, node + n + 1);

	double l = 0, r = 1 + eps;

	while (r - l >= eps) {
		double mid = (l + r) / 2;
		if (check(mid))
			l = mid;
		else
			r = mid;
	}

	printf("%.8lf\n", l);
	return 0;
}
