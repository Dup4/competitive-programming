#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 10;
ll L, R, n, w[N], g[N]; 
int blk, m, tot, pri[N], check[N], id1[N], id2[N];
inline int id(ll x) {
	if (x <= blk) return id1[x];  
	return id2[n / x];
}
void sieve(int n) {
	memset(check, 0, sizeof check);
	tot = 0;
	for (int i = 2; i <= n; ++i) {
		if (!check[i]) pri[++tot] = i;
		for (int j = 1; j <= tot; ++j) {
			if (1ll * i * pri[j] > n) break;
			check[i * pri[j]] = 1;
			if (i % pri[j] == 0) break;
		}
	}
}

ll S(ll x, int y) {
	if (x <= 1 || pri[y] > x) return 0; 
	int k = id(x);
	//y - 1 可能会用到pri[0], 所以不要用*pri来存个数
	//这里是[1, x]中>=y的质数的贡献，他们上一轮选择的是pri[y - 1]，那么他们的次大质因子就是pri[y - 1], 这就是他们的贡献
	ll res = 1ll * pri[y - 1] * (g[k] - y + 1);
	for (int i = y; i <= tot && 1ll * pri[i] * pri[i] <= x; ++i) {
		ll t1 = pri[i], t2 = 1ll * pri[i] * pri[i];
		for (int e = 1; t2 <= x; ++e, t1 = t2, t2 *= pri[i]) {
			res += S(x / t1, i + 1) + pri[i];
		}
	}
	return res;
}

ll solve(ll _n) {
	n = _n; m = 0; blk = sqrt(n); 
	for (ll i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i);
		w[++m] = n / i; g[m] = w[m] - 1;
		if (w[m] <= blk) id1[w[m]] = m;
		else id2[n / w[m]] = m;  
	}
	for (int j = 1; j <= tot && 1ll * pri[j] * pri[j] <= w[1]; ++j) {
		for (int i = 1; 1ll * pri[j] * pri[j] <= w[i] && i <= m; ++i) {
			int k = id(w[i] / pri[j]);
			g[i] -= g[k] - j + 1;
		}
	}
	return S(n, 1);
}


int main() {
	sieve(N - 1);
	while (scanf("%lld%lld", &L, &R) != EOF) {
		printf("%lld\n", solve(R) - solve(L - 1));
	}
	return 0;
}
