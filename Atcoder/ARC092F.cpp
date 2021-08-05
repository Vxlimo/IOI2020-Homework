#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
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
const int N = 1e3;
const int M = 2e5;

int n, m;
int x[M + 1], y[M + 1];
vector<int> to[N + 1];
int reach[N + 1][N + 1], reachs[2][N + 1][N + 1];

inline void addedge(int u, int v)
{
	to[u].push_back(v);
	return;
}
inline void dfs(int u, int from)
{
	reach[from][u] = 1;
	for (int i = 0; i < to[u].size(); i++) {
		int v = to[u][i];
		if (!reach[from][v])
			dfs(v, from);
	}
	return;
}
inline void dfs2(int u, int from, int first, int opt)
{
	reachs[opt][from][u] = first;
	for (int i = 0; i < to[u].size(); i++) {
		int v = to[u][i];
		if (!reachs[opt][from][v])
			dfs2(v, from, first, opt);
	}
	return;
}
int main()
{
	n = read();
	m = read();
	for (int i = 1; i <= m; i++) {
		x[i] = read();
		y[i] = read();
		addedge(x[i], y[i]);
	}

	for (int i = 1; i <= n; i++)
		dfs(i, i);
	for (int i = 1; i <= n; i++) {
		reachs[0][i][i] = reachs[1][i][i] = -1;
		for (int j = 0; j < to[i].size(); j++)
			if (!reachs[0][i][to[i][j]])
				dfs2(to[i][j], i, to[i][j], 0);
		for (int j = to[i].size() - 1; j >= 0; j--)
			if (!reachs[1][i][to[i][j]])
				dfs2(to[i][j], i, to[i][j], 1);
	}

	for (int i = 1; i <= m; i++) {
		int u = x[i], v = y[i];
		printf("%s\n", (reach[v][u] ^ (reachs[0][u][v] != reachs[1][u][v]))?"diff":"same");
	}
	return 0;
}
