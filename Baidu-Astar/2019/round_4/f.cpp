#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
int n, m, k, d[N];

void gao() {
	for (int i = 1; i <= n; ++i)
		if (d[i] < k) {
			puts("No");
			return;
		}
	puts("Yes");
}

int main() {
	int _T; cin >> _T;
	while (_T--) {
		scanf("%d%d%d", &n, &m, &k);
		memset(d, 0, sizeof d);
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			++d[u]; ++d[v];
		}
		gao();
	}
	return 0;
}
