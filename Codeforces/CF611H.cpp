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
const int N = 6;

int n;
int link[N + 1][N + 1], need[N + 1], pre[N + 1];

inline int digit(int x)
{
	int sum = 1;

	while (x / 10) {
		x /= 10;
		sum++;
	}
	return sum;
}
inline bool check()
{
	for (int S = 0; S < 1 << N; S++) {
		int node = 0, edge = 0;
		for (int i = 1; i <= N; i++) {
			if (S & (1 << (i - 1))) {
				node += need[i];
				for (int j = 1; j <= N; j++)
					if (S & (1 << (j - 1)))
						edge += link[i][j];
			}
		}
		if (node && edge >= node)
			return false;
	}
	return true;
}
inline bool find()
{
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (link[i][j]) {
				if (need[i] > 1) {
					link[i][j]--;
					need[i]--;
					if (check()) {
						printf("%d %d\n", pre[i] + need[i], pre[j]);
						return true;
					}
					link[i][j]++;
					need[i]++;
				}
				if (need[j] > 1) {
					link[i][j]--;
					need[j]--;
					if (check()) {
						printf("%d %d\n", pre[i], pre[j] + need[j]);
						return true;
					}
					link[i][j]++;
					need[j]++;
				}
			}
		}
	}
	return false;
}
int main()
{
	n = read();
	for (int i = 1; i < n; i++) {
		string x, y;
		cin >> x >> y;
		link[x.size()][y.size()]++;
	}
	for (int i = 1; i <= n; i++)
		need[digit(i)]++;
	pre[1] = 1;
	for (int i = 2; i <= N; i++)
		pre[i] = pre[i - 1] * 10;

	if (!check()) {
		printf("-1\n");
		return 0;
	}
	while (find())
		;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			if (link[i][j])
				printf("%d %d\n", pre[i], pre[j]);
	}
	return 0;
}
