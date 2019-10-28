#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 10, mod = 998244353;
int pri[N], check[N];
void sieve() {
	memset(check, 0, sizeof check);
	*pri = 0; check[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			pri[++*pri] = i;
		}
		for (int j = 1; j <= *pri; ++j) {
			if (1ll * i * pri[j] >= N) break;
			check[i * pri[j]] = 1;
			if (i % pri[j] == 0) break;
		}
	}
}
ll l, r, k, a[N], f[N];

int main() {
	sieve();
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%lld%lld%lld", &l, &r, &k);
		for (int i = 0; i < r - l; ++i) {
			f[i] = 1;
			a[i] = i + l;
		}
		for (int j = 1; j <= *pri; ++j) {
			for (ll k = max(1ll, (l + pri[j] - 1) / pri[j]); k * pri[j] <= r; ++k) {
				
			}
		}
	}
	return 0;
}
