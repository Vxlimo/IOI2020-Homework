#include <iostream>
#include <cstdlib>
#include <cstdio>
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
const int N = 1e3;

int n;
struct Node {
	ll x, y;
} node[N + 1];
int tot;
int step[33];

int main()
{
	n = read();
	for (int i = 1; i <= n; i++) {
		node[i].x = read();
		node[i].y = read();
		if (((abs(node[i].x) + abs(node[i].y)) & 1))
			tot++;
	}
	if (tot != 0 && tot != n) {
		printf("-1\n");
		return 0;
	}
	if (tot == 0) {
		printf("32\n");
		step[1] = 1;
		for (int i = 2, j = 1; i <= 32; i++, j <<= 1)
			step[i] = j;
		for (int i = 32; i >= 1; i--)
			printf("%d ", step[i]);
		printf("\n");
	} else {
		printf("31\n");
		for (int i = 1, j = 1; i <= 31; i++, j <<= 1)
			step[i] = j;
		for (int i = 31; i >= 1; i--)
			printf("%d ", step[i]);
		printf("\n");
	}

	for (int i = 1; i <= n; i++) {
		ll x = 0, y = 0;
		for (int j = 31 + (tot == 0); j >= 1; j--) {
			if (abs(node[i].x - x) < abs(node[i].y - y)) {
				if (y < node[i].y) {
					putchar('U');
					y += step[j];
				} else {
					putchar('D');
					y -= step[j];
				}
			} else {
				if (x < node[i].x) {
					putchar('R');
					x += step[j];
				} else {
					putchar('L');
					x -= step[j];
				}
			}
		}
		putchar('\n');
	}

	return 0;
}
