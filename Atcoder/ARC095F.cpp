#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>
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
const int N = 1e5;

int n, root;
struct Edge {
	int to, next;
} edge[N * 2 + 1];
int start[N + 1], tot, d[N + 1], sz[N + 1];
vector<int> tag;
int ans[N + 1][2];

inline void addedge(int u, int v)
{
	edge[++tot] = { v, start[u] };
	start[u] = tot;
	d[u]++;
	edge[++tot] = { u, start[v] };
	start[v] = tot;
	d[v]++;
	return;
}
inline void dfs(int u, int fa)
{
	bool flag = false;

	for (int i = start[u]; i; i = edge[i].next) {
		int v = edge[i].to;
		if (v == fa)
			continue;
		dfs(v, u);
		if (d[v] == 1)
			sz[u]++;
		else
			flag = true;
	}
	if (!flag && sz[u]) {
		sz[u]--;
		for (int i = start[u]; i; i = edge[i].next) {
			int v = edge[i].to;
			if (v == fa || v == root)
				continue;
			tag.push_back(v);
			break;
		}
	}
	if (d[u] != 1)
		tag.push_back(u);
	return;
}
inline bool check()
{
	for (int i = 1; i <= n; i++) {
		if (d[i] == 1)
			continue;
		int cnt = 0;
		for (int j = start[i]; j; j = edge[j].next) {
			int v = edge[j].to;
			if (d[v] != 1)
				cnt++;
		}
		if (cnt > 2)
			return false;
		if (cnt <= 1) {
			for (int j = start[i]; j; j = edge[j].next) {
				int v = edge[j].to;
				if (d[v] == 1) {
					root = v;
					break;
				}
			}
		}
	}
	return true;
}
inline void solve(int type)
{
	int cnt = 0;

	for (int i = 0; i < tag.size(); i++) {
		int u = tag[i];
		int st = cnt + 1;
		ans[st + sz[u]][type] = ++cnt;
		for (int j = 1; j <= sz[u]; j++)
			ans[st + j - 1][type] = ++cnt;
	}
	return;
}
inline void print()
{
	int right = 0;

	for (int i = 1; i <= n; i++) {
		if (ans[i][0] < ans[i][1])
			break;
		if (ans[i][1] < ans[i][0]) {
			right = 1;
			break;
		}
	}
	for (int i = 1; i <= n; i++)
		printf("%d ", ans[i][right]);
	printf("\n");
	return;
}
int main()
{
	n = read();
	for (int i = 1; i < n; i++)
		addedge(read(), read());

	if (n == 2) {
		printf("1 2\n");
		return 0;
	}
	if (!check()) {
		printf("-1\n");
		return 0;
	}
	dfs(root, 0);
	tag.push_back(root);
	solve(0);
	reverse(tag.begin(), tag.end());
	solve(1);

	print();
	return 0;
}
