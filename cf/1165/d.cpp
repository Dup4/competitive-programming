#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 510
int n, a[N];
ll res;
set <ll> p, q;

void solve() {
	for (int i = 2; 1ll * i * i <= res; ++i) if (res % i == 0) {
		ll a = i, b = res / i;
		if (a != 1 && a != res) {
			q.insert(a);
		}
		if (b != 1 && b != res) {
			q.insert(b);
		}
	}
	if (p == q) {
		printf("%lld\n", res);
	} else {
		puts("-1");
	}
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		p.clear(); q.clear();
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			p.insert(a[i]);
		}
		sort(a + 1, a + 1 + n);
		res = 1ll * a[1] * a[n];
		solve();
	}
	return 0;
}
