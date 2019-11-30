#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 10, mod = 59964251;
int pri[N], check[N], mu[N], n, m, d, K, phi; 
char s[N]; 
void sieve() {
	memset(check, 0, sizeof check);
	*pri = 0;
	mu[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (check[i] == 0) {
			pri[++*pri] = i;
			mu[i] = -1;
		}
		for (int j = 1; j <= *pri; ++j) {
			if (i * pri[j] >= N) break;
			check[i * pri[j]] = 1;
			if (i % pri[j] == 0) {
				mu[i * pri[j]] = 0;
				break;
			} else {
				mu[i * pri[j]] = -mu[i];
			}
		}
	}
}

int eular(int n) {
	int ans = n;
	for (int i = 2; i * i <= n; ++i) {
		if (n % i == 0) {
			ans -= ans / i;
			while (n % i == 0) 
				n /= i;
		}
	}
	if (n > 1) ans -= ans / n;
	return ans;
}

ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}

ll qmod(ll base, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res = res * base % mod;
		base = base * base % mod;
		n >>= 1;
	}
	return res;
}

int getMod(int mod) {
	int res = 0;
	for (int i = 1; s[i]; ++i) {
		res = (res * 10 + s[i] - '0') % mod;
	}
	return res;
}

int main() {
	phi = eular(mod);
	sieve(); 	
//	cout << phi << endl;
	int _T; scanf("%d", &_T);
	while (_T--) {
		scanf("%s%d%d%d", s + 1, &m, &d, &K);
		int len = strlen(s + 1);
		if (len <= 9) {
			n = 0;
			for (int i = 1; s[i]; ++i) {
				n = n * 10 + s[i] - '0';
			}
		} else {
			n = getMod(phi);
			if (getMod(643) == 0 || getMod(93257) == 0) {
				n += phi;
			}
		}
		ll res = 0;
		for (int i = 1; i <= m / d; ++i) {
			int base = 0;
			for (int j = i * d; j <= m; j += i * d) {
				base += qmod(j, K);
				base %= mod;
			}
			res += 1ll * mu[i] * qmod(base, n) % mod;
			res = (res + mod) % mod;
		}
		printf("%lld\n", res);
	}
	return 0;
}
