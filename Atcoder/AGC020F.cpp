#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <unordered_map>
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
const int mod = 998244353;

string s;
unordered_map<string, int> f;

inline void merge(string &a, string b)
{
	for (int i = 0; i < a.size(); i++)
		if (b[i] == '0')
			a[i] = '0';
	return;
}
inline int dp(string t)
{
	if (!t.size())
		return 1;
	if (f.count(t))
		return f[t];
	int n = t.size(), ans = 0;

	ans = (ans + ((t[0] == '1') ? 2ll : 1ll) * dp(t.substr(1, n)) % mod) % mod;
	for (int i = 1; i * 2 <= n; i++) {
		string w = t.substr(0, i);
		for (int j = 2; i * j <= n; j++) {
			merge(w, t.substr(i * (j - 1), i * j));
			ans = (ans + 1ll * dp(w) * dp(t.substr(i * j, n)) % mod) % mod;
		}
	}
	f[t] = ans;
	return ans;
}
int main()
{
	cin >> s;

	printf("%d\n", dp(s));

	return 0;
}
