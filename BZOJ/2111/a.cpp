#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 2e6 + 10;
int n, m;
ll mod;
ll fac[N], inv[N];
ll qpow(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * base % mod;
		base = base * base % mod;
		n >>= 1;
	}
	return res;
}

ll C(ll n, ll m) {
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
ll Lucas(ll n, ll m) {
    if (n < m) return 0;
	if (m == 0) return 1;
	return Lucas(n / mod, m / mod) * C(n % mod, m % mod) % mod;
}

#define ls (u << 1)
#define rs (u << 1 | 1)
ll sze[N], f[N];
void DFS(int u) {
	sze[u] = 1;
	if (ls <= n) {
		DFS(ls);
		sze[u] += sze[ls];
	}
	if (rs <= n) {
		DFS(rs);
		sze[u] += sze[rs]; 
	}
}

ll DFS2(int u) {
	if (u > n) return 1;
	return DFS2(ls) * DFS2(rs) % mod * Lucas(sze[u] - 1, sze[ls]) % mod;  
}

int main() {
	scanf("%d%lld", &n, &mod);
	m = min(1ll * n, mod - 1); 
	fac[0] = 1;
	for (int i = 1; i <= m; ++i) fac[i] = fac[i - 1] * i % mod; 
	inv[m] = qpow(fac[m], mod - 2);  
	for (int i = m; i >= 1; --i) inv[i - 1] = inv[i] * i % mod;
	DFS(1);
	printf("%lld\n", DFS2(1));
	return 0;
}
