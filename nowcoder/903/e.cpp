#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, a[N], b[N], c[N];

struct BIT {
	int a[N];
	void init() {
		memset(a, 0, sizeof a);
	}
	void update(int x, int val) {
		for (; x < N; x += x & -x) {
			a[x] += val;
		}
	}
	int query(int x) {
		int res = 0;
		for (; x > 0; x -= x & -x) {
			res += a[x];
		}
		return res;
	}
	int query(int l, int r) {
		return query(r) - query(l - 1); 
	}
}bit[2];


int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", a + i, b + i);
			a[i] -= n;
			b[i] -= n;
			c[a[i]] = i;
		}
		for (int i = 1; i <= n; ++i) {
			b[i] = c[b[i]];
		}
		for (int i = 0; i < 2; ++i) {
			bit[i].init();
		}
		for (int i = 1; i <= n; ++i) {
			bit[1].update(b[i], 1);	
		}
		for (int i = 1; i <= n; ++i) {
			bit[1].update(b[i], -1);
			printf("%d\n", bit[0].query(b[i] + 1, n) + bit[1].query(1, b[i] - 1));
			bit[0].update(b[i], 1);
		}
	}
	return 0;
}
