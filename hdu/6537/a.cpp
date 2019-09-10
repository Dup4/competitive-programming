#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 10;
const int mod = 1e9 + 7;
ll n, w[N << 1];
int blk, K, tot, pri[N], check[N], id1[N], id2[N], m, g[N << 1], fac[N], inv[N];
inline int id(ll x) {
	if (x <= blk) return id1[x];
	return id2[n / x];
}
inline void add(int &x, int y) {
	x += y;
	if (x >= mod) x -= mod;
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
inline ll qpow(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * base % mod;
		base = base * base % mod;
		n >>= 1;
	}
	return  res;
}
inline ll Inv(ll x) { return qpow(x, mod - 2); }
inline ll C(int n, int m) {
	if (m < 0) return 0;
	return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod;
}

int S(ll x, int y, int K) { 
	if (x <= 1 || pri[y] > x) {
		return 0;
	}
	int k = id(x);
	int res = 1ll * K * (g[k] - y + 1) % mod;	
	for (int i = y; i <= tot && 1ll * pri[i] * pri[i] <= x; ++i) {
		ll t1 = pri[i], t2 = 1ll * pri[i] * pri[i];
		for (int e = 1; t2 <= x; ++e, t1 = t2, t2 *= pri[i]) {
			add(res, (C(e + K - 1, K - 1) * S(x / t1, i + 1, K) % mod + C(e + K, K - 1)) % mod);
		}
	}
	return res;
}


int main() {
	sieve();
	fac[0] = 1;
	for (int i = 1; i < N; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
	inv[N - 1] = Inv(fac[N - 1]);
	for (int i = N - 1; i >= 1; --i) inv[i - 1] = 1ll * inv[i] * i % mod;
	while (scanf("%lld%d", &n, &K) != EOF) {
		m = 0; blk = sqrt(n);
		//数论分块和预处理h(n, 0)以及g(n, 0)，但是要注意不要把1的贡献算上
		for (ll i = 1, j; i <= n; i = j + 1) {
			j = n / (n / i);
			w[++m] = n / i;
			add(g[m], mod + w[m] - 1);
			//记录位置
			if (w[m] <= blk) {
				id1[w[m]] = m;
			} else {
				id2[n / w[m]] = m;
			}
		}
		//递推，第一维枚举j，就是为了数组只开一维，j那一维直接滚掉就好了
		//g[i][j]表示的是小于等于i的本身就是质数或者最小质因子大于p_j的所有贡献，省掉的是j那一维
		for (int j = 1; j <= tot && 1ll * pri[j] * pri[j] <= w[1]; ++j) {
			for (int i = 1; i <= m && 1ll * pri[j] * pri[j] <= w[i]; ++i) {
				int k = id(w[i] / pri[j]);
				add(g[i], mod - (g[k] - (j - 1) + mod) % mod);
			}
		}
		int res = 0;
		for (int i = 0, t = ((K & 1) ? -1 : 1); i <= K; ++i, t *= -1) {
			add(res, (mod + 1ll * t * C(K, i) % mod * (S(n, 1, i) + 1) % mod) % mod);
		}
		printf("%d\n", res); 
	}
	return 0;
}
