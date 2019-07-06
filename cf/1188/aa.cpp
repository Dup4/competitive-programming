#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, a[N], d[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		memset(d, 0, sizeof d);
		for (int i = 1, u, v; i < n; ++i) {
			scanf("%d%d", &u, &v);
			++d[u]; ++d[v];
		}
		bool F = 1;
		for (int i = 1; i <= n; ++i) if (d[i] == 2) F = 0;
		puts(F ? "YES" : "NO");
	}
	return 0;
}
