#include <bits/stdc++.h>
using namespace std;

#define N 2000010
#define pii pair <int, int>
#define fi first
#define se second
int n, a[N];
pii q[N]; int last;

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			a[i] += a[i - 1];
		}
		for (int i = 1; i <= n; ++i) a[i] *= -1;
		int res = 0;
		last = 0;
		q[++last] = pii(0, 0);
		for (int i = 1; i <= n; ++i) {
			int pos = lower_bound(q + 1, q + 1 + last, pii(a[i] + 1, 0)) - q;
			if (pos <= last) {
				res = max(res, i - q[pos].se);
			}
			if (a[i] > q[last].fi) q[++last] = pii(a[i], i);
		}
		printf("%d\n", res);
	}
	return 0;
}
