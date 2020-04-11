#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 110
#define pii pair <int, int>
#define fi first
#define se second
int n;
pii a[N];
ll b[N];
bool ok() {
	for (int i = 2; i <= n; ++i) {
		if (b[i] <= b[i - 1]) {
			return false;
		}
	}
	return true;
}
void solve() {
	for (int i = 1; i <= 4000; ++i) {
		for (int j = 1; j <= 4000; ++j) {
			for (int k = 1; k <= n; ++k) {
				b[k] = 1ll * i * a[k].fi + 1ll * j * a[k].se;
			}
			if (ok()) {
				printf("%d %d\n", i, j);
				return;
			}
		}
	}
	puts("IMPOSSIBLE");
}

int main() {
	int T; scanf("%d", &T);
	for (int kase = 1; kase <= T; ++kase) {
		printf("Case #%d: ", kase);
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", &a[i].fi, &a[i].se);
		}
		solve();
	}
	return 0;
}
