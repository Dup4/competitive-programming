#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 10;
const ll mod = 1e9 + 7;
ll n, k, d[N]; 
char s[N];
int pri[N], check[N], mu[N];
void sieve() {
	memset(check, 0, sizeof check);
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
			if (i % pri[j] == 0) {
				mu[i * pri[j]] = 0;
				break;
			} else {
				mu[i * pri[j]] = -mu[i]; 
			}
		}
	}
	memset(d, 0, sizeof d);
	for (int i = 1; i < N; ++i)
		for (int j = i; j < N; j += i)
			d[j] = (d[j] + 1ll * i * i * mu[j / i] % mod) % mod; 
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
inline ll inv(ll x) {
	return qpow(x, mod - 2); 
}

inline ll F(ll a1) {
	if (a1 == 1) return (k + mod - 1) % mod;
	ll q = a1;
	ll res = a1 * (1 + mod - qpow(q, k)) % mod * inv((1 + mod - q) % mod) % mod;
	return (res - a1 + mod) % mod; 
}

ll S(ll n) {
	ll res = 0;
	for (int T = 1; T <= n; ++T) {
	//	if (n == 2) cout << T << " " << F(n / T) << " " << d[T] << endl;
		res += F(n / T) * d[T] % mod;
		res %= mod;
	}	
	return res;
}

int main() {
	sieve();
//	cout << d[1] << " " << d[2] << endl; 
	int _T; cin >> _T;
	while (_T--) {
		scanf("%lld%s", &n, s);
		k = 0;
		for (int i = 0; s[i]; ++i) k = (k * 10 + s[i] - '0') % (mod - 1); 
		printf("%lld\n", S(n)); 
	}
	return 0;
}
