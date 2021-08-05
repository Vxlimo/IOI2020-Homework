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
const int N = 4e3;

int n;
string s;
string f[N + 1];
int a[N + 1], b[N + 1], cnta, cntb;
int nxt[N + 1], to[(N << 1) + 1], num[(N << 1) + 1];

inline string minn(string a, string b)
{
	for (int i = 0; i < min(a.size(), b.size()); i++) {
		if (b[i] > a[i])
			return b;
		if (a[i] > b[i])
			return a;
	}
	if (a.size() > b.size())
		return a;
	else
		return b;
}
inline void dp()
{
	for (int i = n; i >= 1; i--) {
		if (a[i] > b[i]) {
			int l = b[i], r = a[i];
			while (l <= r) {
				if (num[l] >= i) {
					if (s[l] == 'a' && to[l] < l)
						f[i] += s[l];
					if (s[l] == 'b' && to[l] > l) {
						f[i] += s[l];
						r = max(r, to[l]);
					}
				}
				l++;
			}
			f[i] += f[num[r + 1]];
		} else {
			f[i] = "ab" + f[nxt[i]];
		}
		f[i] = minn(f[i], f[i + 1]);
	}
	return;
}
int main()
{
	n = read();
	cin >> s;
	for (int i = 0; i < n << 1; i++) {
		if (s[i] == 'a')
			a[++cnta] = i;
		else
			b[++cntb] = i;
	}
	for (int i = 1; i <= n; i++) {
		num[a[i]] = num[b[i]] = i;
		to[a[i]] = b[i];
		to[b[i]] = a[i];
	}
	int j = 2;

	for (int i = 1; i <= n; i++) {
		while ((a[j] <= b[i] || b[j] <= b[i]) && j <= n)
			j++;
		nxt[i] = j;
	}

	dp();

	cout << f[1] << endl;
	return 0;
}
