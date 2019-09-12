#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5 + 10;
const int mod = 1e9 + 7;
ll n, w[N];
int blk, K, pri[N], tot, check[N], prik[N], sprik[N], g[N], h[N], id1[N], id2[N], m;
inline int id(ll x) {
	if (x <= blk) return id1[x];
	return id2[n / x];
}
inline void add(int &x, int y) {
	x += y;
	while (x >= mod) x -= mod;
	while (x < 0) x += mod;
}
inline ll qpow(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * base % mod;
		base = base * base % mod; 
		n >>= 1;
	}
	return res; 
}
void sieve(int n) {
	memset(check, 0, sizeof check);
	tot = 0;
	sprik[0] = 0; 
	for (int i = 2; i <= n; ++i) {
		if (!check[i]) {
			pri[++tot] = i;
			prik[tot] = qpow(i, K);
			sprik[tot] = (sprik[tot - 1] + prik[tot]) % mod;
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

struct Sumk {
	static const int M = 110;
	int S[M][M];
	void init() {
		S[0][0] = 1;
		for (int i = 1; i < M; ++i) {
			for (int j = 1; j <= i; ++j) {
				S[i][j] = (1ll * j * S[i - 1][j] % mod + S[i - 1][j - 1]) % mod;
			}
		}	
	}
	//计算sum i^k   O(k^2)
	inline int calc(ll n, int k) {
		int res = 0;
		for (int i = 1; i <= k; ++i) {
			ll s = 1;
			for (int j = 0; j <= i; ++j) {
				if ((n + 1 - j) % (i + 1)) s = s * ((n + 1 - j + mod) % mod) % mod;
				else s = s * (((n + 1 - j) / (i + 1)) % mod) % mod;
			}
			add(res, s * S[k][i] % mod);
		}
		return res;
	}
}sumk;

inline int F(ll p, int e) {
	return qpow(p, e * K) * (e * K + 1) % mod;
}
int S(ll x, int y) {
	if (x <= 1 || pri[y] > x) {
		return 0;
	}
	int k = id(x);
	int res = 1ll * (K + 1) * ((g[k] - sprik[y - 1] + mod) % mod) % mod;
	cout << x << " " << y - 1 << " " << g[k] << " " << sprik[y - 1] << endl;
	for (int i = y; i <= tot && 1ll * pri[i] * pri[i] <= x; ++i) {
		ll t1 = pri[i], t2 = 1ll * pri[i] * pri[i];
		for (int e = 1; t2 <= x; ++e, t1 = t2, t2 *= pri[i]) {
			add(res, (1ll * F(pri[i], e) * S(x / t1, i + 1) % mod + F(pri[i], e + 1) % mod));
		}
	}
	return res;
}

int main() {
	sumk.init();
	while (scanf("%lld%d", &n, &K) != EOF) {
		m = 0; sieve(blk = sqrt(n)); 
		//数论分块和预处理h(n, 0)以及g(n, 0)，但是要注意不要把1的贡献算上
		for (ll i = 1, j; i <= n; i = j + 1) {
			j = n / (n / i);
			w[++m] = n / i;
			g[m] = (w[m] + mod - 1) % mod;
			h[m] = (sumk.calc(w[m], K) + mod - 1) % mod;
			//记录位置
			if (w[m] <= blk) {
				id1[w[m]] = m;
			} else {
				id2[n / w[m]] = m;
			}
		}
		//递推，第一维枚举j，就是为了数组只开一维，j那一维直接滚掉就好了
		//g[i][j]表示的是小于等于i的本身就是质数或者最小质因子大于p_j的所有贡献，省掉的是j那一维
		for (int j = 1; j <= tot; ++j) {
			for (int i = 1; i <= m && 1ll * pri[j] * pri[j] <= w[i]; ++i) {
				int k = id(w[i] / pri[j]);
				add(g[i], mod - (g[k] - (j - 1) + mod) % mod);
				add(h[i], mod - 1ll * prik[j] * (h[k] - sprik[j - 1] + mod) % mod);
			}
		}
		//注意把特殊的1的贡献加上
		printf("%d\n", (S(n, 1) + 1) % mod); 
	}
	return 0;
}
