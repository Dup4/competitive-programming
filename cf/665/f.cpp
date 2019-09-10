#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 10;
ll n, w[N << 1], g[N << 1];
int blk, pri[N], tot, check[N], sum[N], id1[N], id2[N], m;
inline int id(ll x) {
	if (x <= blk) return id1[x];
	return id2[n / x];
}
void sieve() {  
	memset(check, 0, sizeof check);
	tot = 0;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) pri[++tot] = i;
		for (int j = 1; j <= tot; ++j) {  
			if (1ll * i * pri[j] >= N) break;
			check[i * pri[j]] = 1;  
			if (i % pri[j] == 0) break;
		}
	}
}

int main() {
	sieve();
	while (scanf("%lld", &n) != EOF) {
		m = 0; blk = sqrt(n);
		for (ll i = 1, j; i <= n; i = j + 1) {
			j = n / (n / i);
			w[++m] = n / i;
			g[m] = w[m] - 1;
			if (w[m] <= blk) {
				id1[w[m]] = m;
			} else {
				id2[n / w[m]] = m;
			}
		}
		for (int j = 1; j <= tot; ++j) {
			for (int i = 1; i <= m && 1ll * pri[j] * pri[j] <= w[i]; ++i) {
				int k = id(w[i] / pri[j]);
				g[i] += -(g[k] - (j - 1));
			}
		}
		ll res = 0;
		for (int i = 1; i <= tot; ++i) {
			if (1ll * pri[i] * pri[i] * pri[i] > n) break;
			++res;
		}
		for (int i = 1; i <= tot; ++i) {
			ll t = n / pri[i];
			if (g[id(t)] - i <= 0) break;
			res += g[id(t)] - i;
		}
		printf("%lld\n", res);
	}
	return 0;
}
