#include <bits/stdc++.h>
using namespace std;

#define N 1000010
#define ll long long
ll L, R;
int blk, tot, m;
int pri[N], check[N];
int id1[N], id2[N];
ll w[N], g[N];
void init(int n) {
	memset(check, 0, sizeof check);
	for (int i = 2; i <= n; ++i) {
		if (!check[i]) {
			pri[++tot] = i;
		}
		for (int j = 1; j <= tot; ++j) {
			if (1ll * i * pri[j] > n) {
				break;
			}
			check[i * pri[j]] = 1;
			if (i % pri[j] == 0) {
				break;
			}
		}
	}
}

ll S(ll n, ll x, int y) {
	if (x <= 1 || pri[y] > x) return 0;
	int k = (x <= blk) ? id1[x] : id2[n / x];
//	cout << k << endl;
	ll res = 1ll * pri[y - 1] * (g[k] - y + 1);
	for (int i = y; i <= tot && 1ll * pri[i] * pri[i] <= x; ++i) {
		ll t1 = pri[i], t2 = 1ll * pri[i] * pri[i];
		for (int e = 1; t2 <= x; ++e, t1 = t2, t2 *= pri[i]) {
			res += S(n, x / t1, i + 1) + pri[i];
		}
	}
	return res;
}

ll solve(ll n) {
	tot = m = 0; init(blk = sqrt(n));
//	g[1] = n - 1;
	for (ll i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i);
		w[++m] = n / i; g[m] = w[m] - 1;
		if (w[m] <= blk) {
			id1[w[m]] = m;
		} else {
			id2[n / w[m]] = m;
		}
	}
	for (int j = 1; j <= tot; ++j) {
		for (int i = 1; 1ll * pri[j] * pri[j] <= w[i] && i <= m; ++i) {
			int k = (w[i] / pri[j] <= blk) ? id1[w[i] / pri[j]] : id2[n / (w[i] / pri[j])];
			g[i] -= g[k] - j + 1;
		}
	}
	for (int i = 1; i <= m; ++i) cout << g[i] << " ";;
	return S(n, n, 1);
}


int main() {
	while (scanf("%lld%lld", &L, &R) != EOF) {
		printf("%lld\n", solve(R) - solve(L - 1));
	}
	return 0;
}
