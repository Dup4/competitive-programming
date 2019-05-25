#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, m;
int a[N];

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		memset(a, 0, sizeof a);
		for (int i = 1, l, r; i <= m; ++i) {
			scanf("%d%d", &l, &r);
			++a[l]; --a[r + 1];
		}
		int res = 0;
		for (int i = 1; i <= n; ++i) {
			a[i] += a[i - 1];
			res += (a[i] == m);
		}
		printf("%d\n", res);
	}
	return 0;
}
