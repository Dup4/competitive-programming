#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
const ll p = 998244353;
int n;
ll a[N], b[N];

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", a + i);
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", b + i);
		}
		ll res = 0;
		for (int i = 1; i <= n; ++i) {
			a[i] *= 1ll * i * (n - i + 1);
		}
		sort(a + 1, a + 1 + n);
		sort(b + 1, b + 1 + n, [&](int x, int y) {
			return x > y;		
		});
		for (int i = 1; i <= n; ++i) {
			(res += ((a[i] % p * b[i] % p) % p)) %= p;
		}
		printf("%lld\n", res);
	}
	return 0;
}
