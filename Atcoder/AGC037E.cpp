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
const int N = 1e4;

int n, k;
char s[N + 1], ans[N + 1];
int len;

int main()
{
	n = read();
	k = read();
	scanf("%s", s + 1);
	for (int i = 1; i <= n; i++) {
		s[(n << 1) - i + 1] = s[i];
		ans[i] = s[i];
	}
	for (int i = 2; i <= n + 1; i++) {
		bool flag = true;
		for (int j = i; j <= i + n - 1; j++) {
			if (s[j] < ans[j - i + 1])
				break;
			if (s[j] > ans[j - i + 1]) {
				flag = false;
				break;
			}
		}
		if (flag)
			for (int j = 1; j <= n; j++)
				ans[j] = s[i + j - 1];
	}

	len = 2;
	while (ans[len] == ans[1] && len <= n)
		len++;
	len--;

	if (len * (1 << (k - 1)) >= n || k >= 32) {
		for (int i = 1; i <= n; i++)
			printf("%c", ans[1]);
		printf("\n");
	} else {
		for (int i = 1; i <= len * (1 << (k - 1)); i++)
			printf("%c", ans[1]);
		for (int i = len + 1; len * (1 << (k - 1)) + i - len <= n; i++)
			printf("%c", ans[i]);
		printf("\n");
	}
	return 0;
}
