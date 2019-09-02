#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int N = 1e6 + 10;
const ll mod = 1e9 + 7;
int n, k, l, r;
int pri[N]; bool check[N]; ll mu[N];
void sieve() {
	memset(check, 0, sizeof check);
	memset(mu, 0, sizeof mu);
	*pri = 0;
	mu[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!check[i]) {
			pri[++*pri] = i;
			mu[i] = -1;
		}
		for (int j = 1; j <= *pri; ++j) {
			if (1ll * i * pri[j] >= N) break; 
			check[i * pri[j]] = 1;
			if (i % pri[j] == 0) break;
			else mu[i * pri[j]] = -mu[i];
		}
	}
    mu[0] = 0;	
	for (int i = 1; i < N; ++i) mu[i] += mu[i - 1], mu[i] = (mu[i] % mod + mod) % mod;
}

map <int, ll> mp;
ll f(int x) {
	if (x < N) return mu[x];
	if (mp.find(x) != mp.end()) return mp[x]; 
	ll t = 1;
	for (int i = 2, j; i <= x; i = j + 1) {
		j = x / (x / i);   
		t -= 1ll * (j - i + 1) * f(x / i);
	 	t = (t + mod) % mod;	
	}
	return mp[x] = t;
}

ll qpow(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * base % mod;
		base = base * base % mod;
		n >>= 1;
	}
	return res;
}

int main() {
	sieve();
	scanf("%d%d%d%d", &n, &k, &l, &r);
	mp.clear();
	ll res = 0;	l = (l - 1) / k, r /= k;
	for (int i = 1, j; i <= r; i = j + 1) {
		j = r / (r / i);
		if (i <= l) j = min(j, l / (l / i));
		res += 1ll * (f(j) - f(i - 1) + mod) % mod * qpow(r / i - l / i, n) % mod;
		res %= mod;
	}
	printf("%lld\n", res);
	return 0;
}
