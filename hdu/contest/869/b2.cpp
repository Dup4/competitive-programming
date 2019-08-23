#include <bits/stdc++.h>
using namespace std;

int main {
	int _T; cin >> _T; 
	while (_T--) {
		scanf("%d%d", &n, &q); m = n + 1;
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), b[a[i]] = i; 
		b[m] = INF;
		seg.build(1, 1, m);
		int lstans = 0; 
		for (int _q = 1, op, x, k; _q <= q; ++_q) {
			scanf("%d%d", &op, &x);
			if (op == 1) {
				x ^= lstans;
				seg.update(1, 1, m, a[x]);
			} else {
				scanf("%d", &k);
				k ^= lstans;
				printf("%d\n", lstans = seg.query(1, 1, m, k, x));
			}
		}
	}
	return 0;
}
