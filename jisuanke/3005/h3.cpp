#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int N = 2e5 + 10;
const ll mod = 998244353; 
ll n, res, inv2;
int pri[N], check[N], id1[N], id2[N], m, blk;
ll f1[N], f2[N], g[N], h[N], w[N]; 
void sieve() {
	memset(check, 0, sizeof check);
	memset(f1, 0, sizeof f1);
	memset(f2, 0, sizeof f2);
	*pri = 0;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			pri[++*pri] = i;
			f1[*pri] = (f1[*pri - 1] + 1) % mod;
			f2[*pri] = (f2[*pri - 1] + i) % mod;
		}  
		for (int j = 1; j <= *pri; ++j) {
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
	return res;
}
inline ll sum_1(ll x) {
	x %= mod;
	return x * (x + 1) % mod * inv2 % mod;
}
inline void add(ll &x, ll y) {
	x += y;
	if (x >= mod) x -= mod;
}
inline int id(ll x) {
	if (x <= blk) return id1[x];
	else return id2[n / x];
}
ll getG(ll x) {
	if (x <= 1) return 0;
	return g[id(x)];
}
ll getH(ll x) {
	if (x <= 1) return 0;
	return h[id(x)];
}

int main() {
	sieve(); inv2 = qpow(2, mod - 2);  
	scanf("%lld", &n);
	res = 0;
	for (int i = 1; i <= *pri; ++i) {
		ll p = pri[i];
		while (p * pri[i] <= n) {
		  	p *= pri[i];	
			res += (((n + 1) % mod) * (n / p) % mod - (p % mod) * sum_1(n / p) % mod + mod) % mod;  
			res %= mod;
		}
	}
	m = 0; blk = sqrt(n);
	for (ll i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i);
		w[++m] = n / i;
		h[m] = (w[m] + mod - 1) % mod;
		g[m] = (sum_1(w[m]) + mod - 1) % mod;
		if (w[m] <= blk) id1[w[m]] = m;
		else id2[n / w[m]] = m;
	}
	for (int j = 1; j <= *pri; ++j) {
		for (int i = 1; i <= m && 1ll * pri[j] * pri[j] <= w[i]; ++i) {
			int k = id(w[i] / pri[j]);
			add(g[i], mod - 1ll * pri[j] * (g[k] - f2[j - 1] + mod) % mod);
			add(h[i], mod - (h[k] - f1[j - 1] + mod) % mod);
		}
	}
//	cout << h[id(n)] << endl;
//	cout << g[id(n)] << endl;
	for (ll i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i);
	//    cout << i - 1 << " " << j << endl;	
		add(res, (n + 1) % mod * (n / i) % mod * ((getH(j) - getH(i - 1) + mod) % mod) % mod); 
		add(res, mod - sum_1(n / i) * ((getG(j) - getG(i - 1) + mod) % mod) % mod);
	}
	printf("%lld\n", res);
	return 0;
}
