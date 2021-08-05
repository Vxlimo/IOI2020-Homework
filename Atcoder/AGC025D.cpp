#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
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
const int N = 600;

int n, d1, d2;
int tox1[N + 1], toy1[N + 1], tot1, tox2[N + 1], toy2[N + 1], tot2;
int color[N + 1][N + 1];
int buc[13];

inline int dis(int x1, int y1, int x2, int y2)
{
	return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}
inline void dfs1(int x, int y, int c)
{
	if (x < 0 || x >= 2 * n || y < 0 || y >= 2 * n)
		return;
	if (color[x][y] != -1)
		return;
	color[x][y] = c + 1;
	for (int i = 1; i <= tot1; i++) {
		dfs1(x + tox1[i], y + toy1[i], c ^ 1);
		dfs1(x + tox1[i], y - toy1[i], c ^ 1);
		dfs1(x - tox1[i], y + toy1[i], c ^ 1);
		dfs1(x - tox1[i], y - toy1[i], c ^ 1);
	}
	return;
}
inline void dfs2(int x, int y, int c)
{
	if (x < 0 || x >= 2 * n || y < 0 || y >= 2 * n)
		return;
	if (color[x][y] != 1 && color[x][y] != 2)
		return;
	color[x][y] += c * 10;
	for (int i = 1; i <= tot2; i++) {
		dfs2(x + tox2[i], y + toy2[i], c ^ 1);
		dfs2(x + tox2[i], y - toy2[i], c ^ 1);
		dfs2(x - tox2[i], y + toy2[i], c ^ 1);
		dfs2(x - tox2[i], y - toy2[i], c ^ 1);
	}
	return;
}
int main()
{
	memset(color, -1, 4 * (N + 1) * (N + 1));
	n = read();
	d1 = read();
	d2 = read();
	for (int i = 0; i <= d1 && i < 2 * n; i++) {
		for (int j = 0; j <= d1 && j < 2 * n; j++) {
			if (dis(0, 0, i, j) == d1) {
				tot1++;
				tox1[tot1] = i;
				toy1[tot1] = j;
			}
		}
	}
	for (int i = 0; i <= d2 && i < 2 * n; i++) {
		for (int j = 0; j <= d2 && j < 2 * n; j++) {
			if (dis(0, 0, i, j) == d2) {
				tot2++;
				tox2[tot2] = i;
				toy2[tot2] = j;
			}
		}
	}

	for (int i = 0; i < 2 * n; i++)
		for (int j = 0; j < 2 * n; j++)
			dfs1(i, j, 0);
	for (int i = 0; i < 2 * n; i++)
		for (int j = 0; j < 2 * n; j++)
			dfs2(i, j, 0);

	for (int i = 0; i < 2 * n; i++)
		for (int j = 0; j < 2 * n; j++)
			buc[color[i][j]]++;
	int which;
	if (buc[1] >= n * n)
		which = 1;
	if (buc[2] >= n * n)
		which = 2;
	if (buc[11] >= n * n)
		which = 11;
	if (buc[12] >= n * n)
		which = 12;
	for (int i = 0, k = 0; i < 2 * n && k < n * n; i++) {
		for (int j = 0; j < 2 * n && k < n * n; j++) {
			if (color[i][j] == which) {
				printf("%d %d\n", i, j);
				k++;
			}
		}
	}
	return 0;
}
