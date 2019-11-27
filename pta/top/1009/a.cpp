#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 10;
int n, a[N];
struct BIT {
	ll a[N];
	void init() { memset(a, 0, sizeof a); }
	void update(int x, ll v) { for (; x < N; x += x & -x) a[x] += v; }
	ll query(int x) { ll res = 0; for (; x > 0; x -= x & -x) res += a[x]; return res; }
	ll query(int l, int r) {
		if (l > r) return 0;
		return query(r) - query(l - 1);
	}
}bit[2];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		ll res = 0;	
		for (int i = 1; i <= n; ++i) {
			bit[0].update(a[i], 1);
			bit[1].update(a[i], bit[0].query(a[i] + 1, n));
			res += bit[1].query(a[i] + 1, n); 
		}
		printf("%lld\n", res);
	}
	return 0;
}
